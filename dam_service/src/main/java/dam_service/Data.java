package dam_service;

public class Data {
	private StateEnum state; 
    private double value;
    private long time;
    private boolean manual;
    private int span;

    public Data() {

    }

    public Data(long time, double value, StateEnum state, boolean manual, int span) {
        this.setState(state);
        this.setValue(value);
        this.setTime(time);
        this.setManual(manual);
        this.setSpan(span);
    }

    public StateEnum getState() {
        return this.state;
    }

    public void setState(StateEnum state) {
        this.state = state;
    }

    public double getValue() {
        return this.value;
    }

    public void setValue(double value) {
        this.value = value;
    }

    public long getTime() {
        return this.time;
    }

    public void setTime(long time) {
        this.time = time;
    }

    public boolean isManual() {
        return this.manual;
    }

    public void setManual(boolean manual) {
        this.manual = manual;
    }

    public int getSpan() {
        return this.span;
    }

    public void setSpan(int span) {
        this.span = span;
    }
	
	@Override
	public String toString() {
		return "State: " + this.state.getValue() + " Value: " + Math.floor(this.value * 1000) / 1000  + " Timestamp: " + this.time + " Span: " + this.span + " Is Manual? " + this.manual;
	}
}
