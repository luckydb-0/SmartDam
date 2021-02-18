package dam_service;

class DataPoint {
    private double value;
    private long time;
    private StateEnum state;

    public DataPoint(double value, long time, StateEnum state) {
        this.value = value;
        this.time = time;
        this.setState(state);
    }

    private void setState(StateEnum state) {
        this.state = state;
    }

    public double getValue() {
        return value;
    }

    public long getTime() {
        return time;
    }

    public String getState() {
        return this.state.toString();
    }
}