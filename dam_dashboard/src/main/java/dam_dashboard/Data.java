package dam_dashboard;

public class Data {
	private StateEnum state;
	private double value;
	private long timestamp;
	
	public Data(StateEnum state, double value, long time) {
		this.state = state;
		this.value = value;
		this.timestamp = time;
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
		return timestamp;
	}

	public void setTimestamp(long timestamp) {
		this.timestamp = timestamp;
	}
	
	@Override
	public String toString() {
		return this.state.getValue() + ":" + Math.floor(this.value * 1000) / 1000  + ":" + this.timestamp;
	}
}
