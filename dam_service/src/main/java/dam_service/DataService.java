package dam_service;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;

import java.util.Date;
import java.util.LinkedList;
import java.util.Optional;

/*
 * Data Service as a vertx event-loop 
 */
public class DataService extends AbstractVerticle {

	private int port;
	private static final int MAX_SIZE = 10;
	private LinkedList<Data> values;
	private MessageHandler mh;
	
	public DataService(int httpPort, MessageHandler mh) {
		this.values = new LinkedList<>();
		this.values.add(new Data(0, 0, StateEnum.NORMAL, true, 100));
		this.port = httpPort;
		this.mh = mh;
	}

	@Override
	public void start() {
		Router router = Router.router(vertx);
		router.route().handler(BodyHandler.create());
		router.post("/api/data").handler(this::handleAddNewData);
		router.get("/api/data").handler(this::handleGetData);		
		vertx
			.createHttpServer()
			.requestHandler(router)
			.listen(port);

		log("Service ready.");
	}
	
	private void handleAddNewData(RoutingContext routingContext) {		
		HttpServerResponse response = routingContext.response();
		JsonObject res = routingContext.getBodyAsJson();
		if (res == null) {
			sendError(400, response);
		} else {
			float value = res.getFloat("value");
			StateEnum state = StateEnum.getStateFromValue(Integer.parseInt(res.getString("state")));
			long time = System.currentTimeMillis();
			
			log("New value: " + value + " State: " + state + " on " + new Date(time));
			
			this.mh.sendMessage(state.value + ":" + Math.floor(value * 1000) / 1000  + ":" + time);

			response.setStatusCode(200).end();
		}
	}
	
	private void handleGetData(RoutingContext routingContext) {
		JsonArray arr = new JsonArray();
		for (Data p: values) {
			JsonObject data = new JsonObject();
			data.put("time", p.getTime());
			data.put("value", p.getValue());
			data.put("state", p.getState());
			data.put("manual", p.isManual());
			data.put("span", p.getSpan());
			arr.add(data);
		}
		routingContext.response()
			.putHeader("content-type", "application/json")
			.end(arr.encodePrettily());
	}
	
	private void sendError(int statusCode, HttpServerResponse response) {
		response.setStatusCode(statusCode).end();
	}

	private void log(String msg) {
		System.out.println("[DATA SERVICE] "+msg);
	}
	
	public void addData(Data data) {
		this.values.addFirst(data);
		if (this.values.size() > MAX_SIZE) {
			this.values.removeLast();
		}
		this.values.getFirst();
	}
}