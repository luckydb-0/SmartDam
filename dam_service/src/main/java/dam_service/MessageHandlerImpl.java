package dam_service;

import java.util.Optional;

public class MessageHandlerImpl implements MessageHandler {
	
	/**
	 * Communication channel through which the application and the connected board will be communicating.
	 */
	CommChannel channel;
	
	/**
	 * 
	 * @param selectedPort
	 * 		Port through which the communication will happen.
	 */
	public MessageHandlerImpl(String selectedPort) {
		try {
			this.channel = new SerialCommChannel(selectedPort, 9600);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	/**
	 * {@inheritDoc}
	 */
	@Override
	public Optional<String> receiveMessage() {
		if(this.channel.isMsgAvailable()) {
			try {
				String msg = channel.receiveMsg();
				return Optional.of(msg);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		return Optional.empty();
	}
	
	/**
	 * {@inheritDoc}
	 */
	@Override
	public void sendMessage(String msg) {
		this.channel.sendMsg(msg);
	}

}
