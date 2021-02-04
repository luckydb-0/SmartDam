package dam_service;

import io.vertx.core.Vertx;

/**
 * Application's entry point.
 */
public class DamService {

	public static void main(String[] args) throws Exception {
		String port = "COM3";
		DataHandler dh = new DataHandler(port);
		Object lock = new Object();
		Vertx vertx = Vertx.vertx();
		DataService service = new DataService(8080, dh, lock);
		vertx.deployVerticle(service);
		
		/*ControllerImpl controller = new ControllerImpl(port, dh, lock);
		while (true) {
			controller.update();
		}*/
	}

}
