package simulation;

public class CirclePacking {
	static int counter;
	public static void main(String[] args){
		counter=0;
		double RADIUS = 9;
		for(; RADIUS>2; RADIUS-=2.001){
			generateRing(RADIUS);
		}
		System.out.println(counter);
	}
	
	public static void generateRing(double radius){
		double theta=0;
		double r = radius-1.0001;
		double[] r0 = pol2cart(r,theta);
		System.out.println("Pos: "+(r0[0]+Math.random()*0.0001)+" "+r0[1]+" Vel: 0 0");
		counter++;
		double[] prev = r0.clone();
		double[] current;
		for(;theta<2*Math.PI; theta+=Math.PI/50.0){
			current = pol2cart(r,theta);
			if(distance(current,r0)>2.001&&distance(current,prev)>2.001){
				System.out.println("Pos: "+(current[0]+Math.random()*0.0001)+" "+(current[1]+Math.random()*0.0001)+" Vel: 0 0");
				prev = current.clone();
				counter++;
			}
		}
		
		
	}
	public static double[] pol2cart(double r, double theta){
		double[] toRet = new double[2];
		toRet[0] = r*Math.cos(theta);
		toRet[1] = r*Math.sin(theta);
		return toRet;
		
		
	}
	public static double distance(double[] r0, double r1[]){
		return Math.sqrt(Math.pow(r0[0]-r1[0],2)+Math.pow(r0[1]-r1[1],2));
		
	}
	
}
