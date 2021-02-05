package dam_service;

import io.vertx.core.Vertx;

/**
 * Application's entry point.
 */
public class DamService {

	public static void main(String[] args) throws Exception {
		String port = "COM3";
		DataHandler dh = new DataHandler(port);
		Vertx vertx = Vertx.vertx();
		DataService service = new DataService(8080, dh);
		vertx.deployVerticle(service);
		
		while(true) {
			dh.read();
		}
	}

}
