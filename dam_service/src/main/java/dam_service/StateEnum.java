package dam_service;

public enum StateEnum {
	NORMAL(0),
	PRE_ALARM(1),
	ALARM(2);
	
	int value;
	
	StateEnum(int value) {
		this.value = value;
	}
	
	public int getValue() {
		return this.value;
	}
	
	static StateEnum getStateFromValue(int value) {
		switch(value) {
			case 0:
				return StateEnum.NORMAL;
			case 1:
				return StateEnum.PRE_ALARM;
			case 2:
				return StateEnum.ALARM;
			default:
				return null;
		}
	}
}
