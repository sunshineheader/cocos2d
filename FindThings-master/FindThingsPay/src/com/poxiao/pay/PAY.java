package com.poxiao.pay;

public enum PAY {

	PayGold1(1, "新手礼包", 1000, "免费玩3局,需要X.XX元"), 
	PayGold2(2, "复活道具", 1000, "继续游戏,需要X.XX元"),
	PayGold3(3, "提示礼包", 1000, "找不到我来帮你，20个提示,需要X.XX元"),
	PayGold4(4, "时间礼包", 1000, "快增加些时间继续游戏,20个加时道具,需要X.XX元"),
	PayGold5(5, "过关礼包", 1000, "恭喜过关，奖励10个加时、10个提示道具,需要X.XX元"),
	PayGold6(6, "幸运礼包", 1000, "你的名次落后其他人，随机获得20个道具,需要X.XX元"),
	PayGold7(7, "时间奖励", 1000, "恭喜你找对20个物品，获得20秒时间,需要X.XX元"),
	PayGold8(8, "过关礼包", 0, "恭喜过关，奖励1个加时、1个提示道具,需要X.XX元"),
	PayGold9(9, "时间奖励", 0, "恭喜你找对20个物品，获得20秒时间,需要X.XX元");

	// 成员变量
	private int type;
	private String desc;
	private int money;
	private String name;

	// 构造方法
	private PAY(int type, String name, int money, String desc) {
		this.type = type;
		this.name = name;
		this.money = money;
		this.desc = desc;
	}

	// 普通方法
	public static String getName(int type) {
		for (PAY c : PAY.values()) {
			if (c.getType() == type) {
				return c.name;
			}
		}
		return null;
	}

	public static int getMoney(int type) {
		for (PAY c : PAY.values()) {
			if (c.getType() == type) {
				return c.money;
			}
		}
		return 0;
	}

	public static String getDesc(int type) {
		for (PAY c : PAY.values()) {
			if (c.getType() == type) {
				return c.desc;
			}
		}
		return null;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getType() {
		return type;
	}

	public void setType(int type) {
		this.type = type;
	}

	public String getDesc() {
		return desc;
	}

	public void setDesc(String desc) {
		this.desc = desc;
	}

	public int getMoney() {
		return money;
	}

	public void setMoney(int money) {
		this.money = money;
	}

}
