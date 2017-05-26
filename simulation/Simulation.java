package simulation;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;
import com.jmatio.io.*;
import com.jmatio.types.*;


public class Simulation {
	
	//TODO UPDATE MUTEST TO INCLUDE NEW GETDATA METHOD
	
	public static void muTest() throws FileNotFoundException{
		PrintWriter m = new PrintWriter(new File("MU_"+Constants.WMU+"_"+Constants.bound_vel+"_"+Constants.NUM_OF_DISKS+".txt"));
		for(int d = 0; d<=50; d+= 1){
			Constants.MU = d/100.0;
		
			initializeDisks();
			ArrayList<Collision> current;
			double totalAvg = 0;		
			double totalTime = 0;
			for(int i=0;i<Constants.ITERATIONS; i++){		
				totalAvg 	+= Disks.getDist2Center();
				current = Disks.nextCollision();	
				totalTime += current.get(0).time;
				Disks.updatePositions(current.get(0).time, totalTime);
				for(Collision c : current){
					c.process();			
				}
			}	
			totalAvg/=Constants.ITERATIONS;
			m.println(Constants.MU+" "+totalAvg);
		}
		m.close();
	}
	public static void wmuTest() throws FileNotFoundException{
		PrintWriter m = new PrintWriter(new File("WMU_"+Constants.MU+"_"+Constants.bound_vel+"_"+Constants.NUM_OF_DISKS+".txt"));
		for(int d = 0; d<=80; d++){
			Constants.WMU = d/10.0;
		
			initializeDisks();
			ArrayList<Collision> current;
			double totalAvg = 0;		
			double totalTime = 0;
			for(int i=0;i<Constants.ITERATIONS; i++){		
				totalAvg 	+= Disks.getAngVel();
				current = Disks.nextCollision();		
				totalTime += current.get(0).time;
				Disks.updatePositions(current.get(0).time, totalTime);
				for(Collision c : current){
					c.process();			
				}
			}	
			totalAvg/=Constants.ITERATIONS;
			m.println(Constants.WMU+" "+totalAvg);
		}
		m.close();
	}
	public static void boundvelTest() throws FileNotFoundException{
		PrintWriter m = new PrintWriter(new File("AMP_"+Constants.MU+"_"+Constants.WMU+"_"+Constants.NUM_OF_DISKS+".txt"));
		for(double d = 5; d<=50; d+= 2){
			Constants.bound_vel = d/10.0;
		
			initializeDisks();
			ArrayList<Collision> current;
			double totalAvg = 0;		
			double totalTime = 0;
			for(int i=0;i<Constants.ITERATIONS; i++){		
				totalAvg 	+= Disks.getAngVel();
				current = Disks.nextCollision();	
				totalTime += current.get(0).time;
				Disks.updatePositions(current.get(0).time, totalTime);
				for(Collision c : current){
					c.process();			
				}
			}	
			totalAvg/=Constants.ITERATIONS;
			m.println(Constants.bound_vel+" "+totalAvg);
		}
		m.close();
	}
	
	
	public static void DisknumTest() throws FileNotFoundException{
		DataOption DATA = DataOption.ANG_VEL;
		
		PrintWriter m = new PrintWriter(new File("DataOutput"+DATA+"vsN.txt"));
		for(int d = 10; d<=56; d++){
			Constants.NUM_OF_DISKS = d;
			
			initializeDisks();
			ArrayList<Collision> current;
			double totalAvg = 0;	
			double totalTime = 0;
			for(int i=0;i<Constants.ITERATIONS; i++){	
				
				totalAvg 	+= Disks.getData(DATA,0);
				current = Disks.nextCollision();	
				totalTime += current.get(0).time;
				Disks.updatePositions(current.get(0).time, totalTime);
				for(Collision c : current){
					c.process();			

				}
			}	
			totalAvg/=Constants.ITERATIONS;//(totalTime/1000.0);
			m.println(Constants.NUM_OF_DISKS+" "+totalAvg);
		}
		m.close();
	}
	
	public static void testing(String[] args) throws FileNotFoundException{
		setConstants(args);
		if(Constants.MU==-1){
			muTest();
			return;
		}else if(Constants.WMU==-1){
			wmuTest();
			return;
		}else if(Constants.bound_vel==-1){
			boundvelTest();
			return;
		}else{
			DisknumTest();
			return;
		}
		
	}
	
	
	public static void main(String[] args) throws FileNotFoundException{
		DataOption DATA = DataOption.ANG_VEL;
		
		
		// Initialize all variables
		int testing = Integer.parseInt(args[6]);
		int hist = Integer.parseInt(args[7]);
		
		if(testing==1){
			testing(args);
			return;
		}
		
		boolean makeHistograms = false;
		if(hist==1){
			makeHistograms = true;
		}
		
		
		
		
		setConstants(args);
		initializeDisks();
		
		
		PrintWriter p = new PrintWriter(new File("input/sim_data.txt"));
		PrintWriter hist_s = null, hist_w=null;
		if(makeHistograms) {
			hist_s = new PrintWriter(new File("hist_data_s.txt"));
			hist_w = new PrintWriter(new File("hist_data_w.txt"));
		}
		
		long start = System.currentTimeMillis();
		
		int nonce = 0;
		double totalAvg = 0, currentData = 0,  totalTime = 0;
		
		ArrayList<Collision> currentCollision;
		currentData = Disks.getData(DATA, 0);
		double pastData = currentData;
		
		System.out.println("Initial Data: "+currentData+"<br>");

		for(int i=0;i<Constants.ITERATIONS; i++){
			
			
			totalAvg 	+= currentData;
			currentCollision = Disks.nextCollision();	
			totalTime+=currentCollision.get(0).time;
			Disks.updatePositions(currentCollision.get(0).time, totalTime);
			
			for(Collision c : currentCollision){
				c.process();
				p.println(c.toString()+" "+nonce);	 //This is the print for the animation
			}
			currentData = Disks.getData(DATA, 0);
			nonce++;
			
			
			if(makeHistograms){
				if(!currentCollision.get(0).isSwirl()&&!currentCollision.get(0).isBoundary()){
					hist_s.println(currentData-pastData);
				}
				else if(currentCollision.get(0).isBoundary()){
					hist_w.println(currentData-pastData);
				}
			}
	
			pastData = currentData;
		
			
		}
		
		System.out.println("Final Data: "+currentData+"<br>");
		
		totalAvg/=Constants.ITERATIONS;
		System.out.println("Average Data: "+totalAvg+"<br>");
		long end = System.currentTimeMillis();
		
		System.out.printf("Simulation took %d milliseconds.\n",(end-start));
		
		p.close();
		if(makeHistograms){
			hist_s.close();
			hist_w.close();
		}
	}
	
	
	  
	
	public static void setConstants(String[] args) throws FileNotFoundException{
		Constants.MU = Double.parseDouble(args[0]);
		Constants.WMU = Double.parseDouble(args[1]);
		Constants.bound_vel = Double.parseDouble(args[2])/1000.0;
		Constants.NUM_OF_DISKS = Integer.parseInt(args[3]);
		if(Integer.parseInt(args[4])>0){
			Constants.SPINNING = true;
		}else{
			Constants.SPINNING = false;
		}
		Constants.BOUNDRAD = Double.parseDouble(args[5]);
		
		//THIS IS FOR THE ANIMATION
		File argFile = new File("args.txt");
		PrintWriter p = new PrintWriter(argFile);
		p.printf("%.9f\n%d\n%.9f\n%s\n_\n_\n_\n_\n", 1000*Constants.bound_vel,Constants.NUM_OF_DISKS,Constants.BOUNDRAD,args[4]);
		
		p.close();
		
	}
	
	public static void initializeDisks() throws FileNotFoundException{
		Scanner input = new Scanner(new File("input/input.txt"));

		input.nextLine();
		Disks.init();
		Disk toAdd;
		double pos[];
		double vel[];
		String[] toParse;
		for(int i=0; i<Constants.NUM_OF_DISKS; i++){
			toAdd = new Disk();
			pos = new double[Constants.DIMENSIONS];
			vel = new double[Constants.DIMENSIONS];
			toParse = input.nextLine().split(" ");
			for(int j=1;j<=Constants.DIMENSIONS;j++){
				pos[j-1] = Double.parseDouble(toParse[j]);
			}
			toAdd.pos = pos;
			toAdd.theta = 0;
			toAdd.theta_vel = 0;
		
			for(int j=Constants.DIMENSIONS+2;j<2*Constants.DIMENSIONS+2;j++){
				vel[j-Constants.DIMENSIONS-2] = Double.parseDouble(toParse[j]);
			}
			toAdd.vel = vel;
			Disks.add(toAdd);
		}
		input.close();
	}
	
}
