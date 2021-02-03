package dam_service;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;

public class ControllerImpl {
	
	private MessageHandler handler;
	private Double lastDistance;
	private StateEnum lastState;
	
	public ControllerImpl(String port) {
		this.handler = new MessageHandlerImpl(port);
		try {
			Thread.sleep(4000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
	
	private void readData() throws IOException {
		URL url = new URL("http://localhost:8080/api/data");
        BufferedReader read = new BufferedReader(
        new InputStreamReader(url.openStream()));
        String i;
        while ((i = read.readLine()) != null)
            System.out.println(i);
        read.close();
	}
	
	public void update() throws IOException {
	    /*Data foo = new Data(1, 0.45663232, (long)(23143242));
	    ObjectMapper mapper = new ObjectMapper();

	    String jsonStr = mapper.writeValueAsString(foo);
	    Data result = mapper.readValue(jsonStr, Data.class);
		Gson gson = new Gson();
	    Data foo = new Data(1, 0.45663232, (long)(23143242));

	    String jsonStr = gson.toJson(foo);
	    Data result = gson.fromJson(jsonStr, Foo.class);*/
	}

}
