package dam_service;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class DataHandler {
	
	private List<Data> data;
	private MessageHandler messageHandler;
	
	public DataHandler(String port) {
		this.data = new ArrayList<>();
		this.messageHandler = new MessageHandlerImpl(port);
	}
	
	public void addAndHandleData(Data data) {
		this.data.add(data);
		this.handleData();
	}
	
	private void handleData() {
		Data data = this.data.get(this.data.size() - 1);
		this.messageHandler.sendMessage(data.toString());
	}
}
