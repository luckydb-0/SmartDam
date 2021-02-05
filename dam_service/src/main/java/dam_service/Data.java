package dam_service;

public class Data {
	private int state;
	private double value;
	private long timestamp;
	
	public Data(int state, double value, long time) {
		this.state = state;
		this.value = value;
		this.timestamp = time;
	}

	public int getState() {
		return state;
	}

	public void setState(int state) {
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
		return this.state + ":" + Math.floor(this.value * 1000) / 1000  + ":" + this.timestamp;
	}
}
