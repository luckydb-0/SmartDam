package dam_service;

class DataPoint {
    private double value;
    private long time;
    private StateEnum state;

    public DataPoint(double value, long time, int state) {
        this.value = value;
        this.time = time;
        this.setState(state);
    }

    private void setState(int state) {
        switch(state) {
        case 0:
            this.state = StateEnum.NORMAL;
            break;
        case 1:
            this.state = StateEnum.PRE_ALARM;
            break;
        case 2:
            this.state = StateEnum.ALARM;
            break;
        default:
            break;
        }
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