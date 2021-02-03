package dam_service;

import java.util.Optional;

/**
 * 
 * Class to handle the message exchange between the application and the Arduino board.
 */
public interface MessageHandler {

	/**
	 * 
	 * @return
	 * 		Optional string containing the new message received.
	 */
	Optional<String> receiveMessage();

	/**
	 * 
	 * @param msg
	 * 		The message that needs to be sent to the board.
	 */
	void sendMessage(String msg);

}