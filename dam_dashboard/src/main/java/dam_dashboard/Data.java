package dam_dashboard;

public class Data {

	private StateEnum state; 
	private double value;
	private long time;
	
	public Data() {
		
	}
	
	public Data(long time, double value, StateEnum state) {
		this.state = state;
		this.value = value;
		this.time = time;
	}
	
	public Data(long time, double value, String state) {
		this.state = StateEnum.NORMAL;
		this.value = value;
		this.time = time;
	}

	public StateEnum getState() {
		return state;
	}

	public void setState(StateEnum state) {
		this.state = state;
	}

	public double getValue() {
		return value;
	}

	public void setValue(double value) {
		this.value = value;
	}

	public long getTimestamp() {
		return time;
	}

	public void setTimestamp(long timestamp) {
		this.time = timestamp;
	}
	
	@Override
	public String toString() {
		return this.state.getValue() + ":" + Math.floor(this.value * 1000) / 1000  + ":" + this.time;
	}
}
