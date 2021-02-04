package dam_service;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;

public class ControllerImpl {
	
	private MessageHandler messageHandler;
	private Double lastDistance;
	private StateEnum lastState;
	private DataHandler dataHandler;
	Object lock;
	int i;
	
	public ControllerImpl(String port, DataHandler dh, Object lock) {
		this.messageHandler = new MessageHandlerImpl(port);
		this.dataHandler = dh;
		this.lock = lock;
		i = 0;
		try {
			Thread.sleep(4000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
	}
	
	private void readData() throws IOException {
		/*URL url = new URL("http://localhost:8080/api/data");
		ObjectMapper objectMapper = new ObjectMapper();
        BufferedReader read = new BufferedReader(
        new InputStreamReader(url.openStream()));
        String i;
        String json = "";
        read.readLine();
        while ((i = read.readLine()) != null && i != "}, {") {
        	json += i;
        }
        json += " }]";
        System.out.println(json);
    	objectMapper.readValue(json, Data.class);
        read.close();*/
	}
	
	public void update() {
	    try {
			this.readData();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
