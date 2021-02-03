package dam_service;

import io.vertx.core.Vertx;

/**
 * Application's entry point.
 */
public class DamService {

	public static void main(String[] args) throws Exception {
		String port = "COM3";
		Vertx vertx = Vertx.vertx();
		DataService service = new DataService(8080);
		vertx.deployVerticle(service);
		
		ControllerImpl controller = new ControllerImpl(port);
		while (true) {
			controller.update();
		}
	}

}
