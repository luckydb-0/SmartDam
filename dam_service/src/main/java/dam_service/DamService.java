package dam_service;

import java.util.Optional;

import io.vertx.core.Vertx;

/**
 * Application's entry point.
 */
public class DamService {

	public static void main(String[] args) throws Exception {
		String port = "COM3";
		MessageHandler mh = new MessageHandlerImpl(port);
		Vertx vertx = Vertx.vertx();
		DataService service = new DataService(8080, mh);
		vertx.deployVerticle(service);
		
		new Receiver(mh, service).start();
	}

}
