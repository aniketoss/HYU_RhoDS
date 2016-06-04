/**
 * 
 */
package src;

public class Audi_a6 extends Medium implements Car, Internal {

	String nAme = "Audi_A6";
	private int Displayment;
	private int ID;
	private int maxSpeed;
	private int Speed=0;
	
	public Audi_a6() {
		// TODO Auto-generated constructor stub
	}

	public int getSpeed() {
		return this.Speed;
	}

	public void setSpeed(int Speed) {
		this.Speed = Speed;
	}
	
	public int getDisplayment() {
		return Displayment;
	}

	public void setDisplayment(int displayment) {
		Displayment = displayment;
	}

	public int getID() {
		return ID;
	}

	public void setID(int iD) {
		ID = iD;
	}
	
	public void Print(){
		System.out.println("Name: "+ this.nAme +" "+"배기량 : "+ this.Displayment+" "+"ID: "+ this.ID);
	}
	

	public int getMaxSpeed() {
		return maxSpeed;
	}

	public void setMaxSpeed(int maxSpeed) {
		this.maxSpeed = maxSpeed;
	}


	@Override
	public void SpeedUP() {
		// TODO Auto-generated method stub
		while(Speed < this.maxSpeed)	
		{	
			this.Speed += 30;
			if(Speed > maxSpeed)
				System.out.println(this.nAme+" "+"현재속도: "+this.maxSpeed);
			else
				System.out.println(this.nAme+" "+"현재속도: "+this.Speed);
		}
		System.out.println(this.nAme+" "+"최대 속도 도달  감속하세요");

	}

	@Override
	public void SpeedDown() {
		// TODO Auto-generated method stub
		while(Speed > 0)	
		{	
			this.Speed-= 30;
			if(Speed < 0)
				System.out.println(this.nAme+" "+"현재속도: "+0);
			else
				System.out.println(this.nAme+" "+"현재속도: "+this.Speed);
		}
		System.out.println(this.nAme+" "+"Stop!");

	}
	
	public void Break()
	{
		this.Speed = 0;
	}
	
	public void where_from()
	{	
		System.out.println(this.nAme+": 외제차.");
	}
	
	public  void what_is_type()
	{
		super.type = "중형";
		System.out.println(this.nAme+" "+"차 종류: "+ type);
	}
}
