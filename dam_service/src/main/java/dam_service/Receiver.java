package dam_service;

import java.util.Optional;

public class Receiver extends Thread {
	
	private MessageHandler mh;
	DataService service;
	
	public Receiver(MessageHandler mh, DataService service) {
		this.mh = mh;
		this.service = service;
	}
	
	public void run() {
		while(true) {
			Optional<String> arduinoMsg = mh.receiveMessage();
			if(arduinoMsg.isPresent()) {
				String msg = arduinoMsg.get();
				System.out.println(msg);
				StateEnum state = StateEnum.getStateFromValue(Integer.parseInt(msg.split(":")[0]));
				double value = Double.parseDouble(msg.split(":")[1]);
				long time = System.currentTimeMillis();
				int span = 0;
				boolean isManual = false;
				if(state.equals(StateEnum.ALARM)) {
					span = Integer.parseInt(msg.split(":")[2]);
					isManual = msg.split(":")[3].equals("1") ? true : false;							
				}

				
				this.service.addData(new Data(time, value, state, isManual, span));
			}
		}
	}
}
