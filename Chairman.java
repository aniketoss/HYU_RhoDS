package src;

public class Chairman extends Heavy implements Car, Domestic {
	
	String nAme = "Chairman";
	public int Displayment;
	public int ID;
	public int maxSpeed;
	public int Speed;
	
	public Chairman() {
		// TODO Auto-generated constructor stub
	}
	
	public Chairman(int Displayment, int ID, int maxSpeed)
	{
		this.Displayment = Displayment;
		this.ID = ID;
		this.maxSpeed = maxSpeed;
	}

	public void Print(){
		System.out.println("Name: "+ this.nAme +" "+"배기량 : "+ this.Displayment+" "+"ID: "+ this.ID);
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
		System.out.println(this.nAme+": 국산차.");
	}
	
	public  void what_is_type()
	{
		super.type = "대형";
		System.out.println(this.nAme+" "+"차 종류: "+ type);
	}

}
