///////////////////////////////////////////////////////////////////////////////
//FILE: 'class_functions.cpp'
//
// Member functions of 'Cadac' class hierarchy
// Member functions of class 'Variable'
// 
//010628 Created by Peter H Zipfel
//011129 Adapted to SRAAM6 simulation, PZi
///////////////////////////////////////////////////////////////////////////////

#include "class_hierarchy.hpp"
#include "global_header.hpp"

///////////////////////////////////////////////////////////////////////////////
//////////////// Member functions of 'Cadac' class hierarchy //////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//Constructor initializing   
//
//001220 Created by Peter H Zipfel
//011129 Adapted to SRAAM6 simulation, PZi
///////////////////////////////////////////////////////////////////////////////

Flat6::Flat6()
{
	//creating module-variable array
	flat6=new Variable[NFLAT6];
	if(flat6==0){cerr<<"*** Error: flat6[] allocation failed ***\n";system("pause");exit(1);}

	//zeroeing module-variable array
	for(int i=0;i<NFLAT6;i++)flat6[i].init("empty",0," "," "," "," ");
}
///////////////////////////////////////////////////////////////////////////////
//Constructor initializing the modules and the module-variable arrays
//Reading input data from 'input.asc' and putting into 'flat6' and 'missile' arrays 
//Writing banners to screen, 'tabout.asc' and to 'traj.asc' files  
//
//Module-variable arrays:
//	missile[NMISSILE]		contains variables of modules under class 'Missile'
//	missile6[nmissile6]	contains variables of all modules with empty slots removed
//	scrn_missile6[nscrn_missile6]	contains variables to be displayed at screen and 'tabout.asc'
//	plot_missile6[nplot_missile6] contains variables to be plotted, i.e., written to 'traj.asc'
//	com_missile6[ncom_missile6] contains variables for communication among vehicles
//  event_ptr_list[NEVENT] event pointer list
//
//Index pointer arrays:	
//	flat6_scrn_ind[flat6_scrn_count];
//	missile_scrn_ind[missile_scrn_count];
//	flat6_plot_ind[flat6_plot_count];
//	missile_plot_ind[missile_plot_count];
//	flat6_com_ind[flat6_com_count];
//	missile_com_ind[missile_com_count];
//
//				  
//001220 Created by Peter H Zipfel
//011129 Adapted to SRAAM6 simulation, PZi
///////////////////////////////////////////////////////////////////////////////

Missile::Missile(Module *module_list,int num_modules,int num_target)
{
	int i(0);

	//creating module-variable array
	missile=new Variable[NMISSILE];
	if(missile==0){cerr<<"*** Error: missile[] allocation failed ***\n";system("pause");exit(1);}

	//zeroeing module-variable array
	for(i=0;i<NMISSILE;i++)missile[i].init("empty",0," "," "," "," ");

	//calling initializer modules to build 'flat6' and 'missile' arrays
	//and make other initial calculations in the following sequence

	//call the module definitions -MOD
	for (int j=0;j<num_modules;j++)
		{
			if((module_list[j].name=="environment")&&(module_list[j].definition=="def"))
				def_environment();
			else if((module_list[j].name=="kinematics")&&(module_list[j].definition=="def"))
				def_kinematics();
			else if((module_list[j].name=="newton")&&(module_list[j].definition=="def"))
				def_newton();
			else if((module_list[j].name=="euler")&&(module_list[j].definition=="def"))
				def_euler();
			else if((module_list[j].name=="aerodynamics")&&(module_list[j].definition=="def"))
				def_aerodynamics();
			else if((module_list[j].name=="propulsion")&&(module_list[j].definition=="def"))
				def_propulsion();
			else if((module_list[j].name=="forces")&&(module_list[j].definition=="def"))
				def_forces();
			else if((module_list[j].name=="actuator")&&(module_list[j].definition=="def"))
				def_actuator();
			else if((module_list[j].name=="tvc")&&(module_list[j].definition=="def"))
				def_tvc();
			else if((module_list[j].name=="control")&&(module_list[j].definition=="def"))
				def_control();
			else if((module_list[j].name=="guidance")&&(module_list[j].definition=="def"))
				def_guidance();
			else if((module_list[j].name=="seeker")&&(module_list[j].definition=="def"))
				def_seeker();
			else if((module_list[j].name=="intercept")&&(module_list[j].definition=="def"))
				def_intercept();
		}

	//sizing module-variable arrays 'missile6','scrn_missile6','plot_missile6' arrays
	//their dimensions are the protected data:'nmissile6','nscrn_missile6','nplot_missile6'
	sizing_arrays();

	//allocating dynamic memory to the module-variable arrays
	missile6=new Variable[nmissile6];		
	if(!missile6){cerr<<"*** Error: missile6[] allocation failed *** \n";system("pause");exit(1);}

	scrn_missile6=new Variable[nscrn_missile6];
	if(!scrn_missile6){cerr<<"*** Error: scrn_missile6[] allocation failed *** \n";system("pause");exit(1);}

	plot_missile6=new Variable[nplot_missile6];
	if(!plot_missile6){cerr<<"*** Error: plot_missile6[] allocation failed *** \n";system("pause");exit(1);}

	com_missile6=new Variable[ncom_missile6];
	if(!com_missile6){cerr<<"*** Error: com_missile6[] allocation failed *** \n";system("pause");exit(1);}

	// allocating memory for the screen index arrays
	flat6_scrn_ind=new int[flat6_scrn_count];
	missile_scrn_ind=new int[missile_scrn_count];

	// allocating memory for the plot index arrays
	flat6_plot_ind=new int[flat6_plot_count];
	missile_plot_ind=new int[missile_plot_count];

	// allocating memory for the com index arrays
	flat6_com_ind=new int[flat6_com_count];
	missile_com_ind=new int[missile_com_count];

	//allocating memory for the 'grnd_range' array
	grnd_range=new double[num_target];

	//allocating memory to each event object in event object list
	for (i=0;i<NEVENT;i++)
		event_ptr_list[i]=new Event;

	//initializing the event array index
	nevent=0;
	event_total=0;

	//building 'missile6' array (compacting and merging 'flat6' and 'missile' arrays)
	vehicle_array();

	//building 'scrn_missile6' array from 'missile6' array
	scrn_array();

	//building 'plot_missile6' array from 'missile6' array
	plot_array();

	//building the index arrays of the data to be written to the screen
	scrn_index_arrays();

	//building the index arrays of the data to be written to the 'ploti.asc' files
	plot_index_arrays();

	//building the index arrays of the data to be loaded into the packets of 'combus'
	com_index_arrays();
}
///////////////////////////////////////////////////////////////////////////////
//Destructor deallocating dynamic memory
//				  
//010115 Created by Peter H Zipfel
//011129 Adapted to SRAAM6 simulation, PZi
///////////////////////////////////////////////////////////////////////////////

Missile::~Missile()
{
	delete [] missile;
	delete [] missile6;
	delete [] flat6;
	delete [] scrn_missile6;
	delete [] plot_missile6;
	delete [] com_missile6;
	delete [] flat6_scrn_ind;
	delete [] missile_scrn_ind;
	delete [] missile_plot_ind;
	delete [] flat6_com_ind;
	delete [] missile_com_ind;
	delete [] grnd_range;
	delete [] &event_ptr_list;
}
///////////////////////////////////////////////////////////////////////////////
//Constructor allocating array memeory and initializing  
//
//001220 Created by Peter H Zipfel
//011129 Adapted to SRAAM6 simulation, PZi
///////////////////////////////////////////////////////////////////////////////

Flat3::Flat3()
{
	//creating module-variable array
	flat3=new Variable[NFLAT3];
	if(flat3==0){cerr<<"*** Error: flat3[] allocation failed ***\n";system("pause");exit(1);}

	//zeroeing module-variable array
	for(int i=0;i<NFLAT3;i++)flat3[i].init("empty",0," "," "," "," ");
}
///////////////////////////////////////////////////////////////////////////////
//Constructor initializing the modules and the module-variable arrays
//				  
//010205 Created by Peter H Zipfel
//011129 Adapted to SRAAM6 simulation, PZi
///////////////////////////////////////////////////////////////////////////////

Target::Target(Module *module_list,int num_modules)
{
	//creating module-variable array
	target=new Variable[NTARGET];
	if(target==0){cerr<<"*** Error: target[] allocation failed ***\n";system("pause");exit(1);}

	//zeroeing module-variable array
	for(int i=0;i<NTARGET;i++)target[i].init("empty",0," "," "," "," ");
	//calling initializer modules to build 'flat3' and 'target' arrays
	//and make other initial calculations 

	//call the module definitions
	for (int j=0;j<num_modules;j++)
		{
			if((module_list[j].name=="environment")&&(module_list[j].definition=="def"))
				def_environment();
			else if((module_list[j].name=="guidance")&&(module_list[j].definition=="def"))
				def_guidance();
			else if((module_list[j].name=="control")&&(module_list[j].definition=="def"))
				def_control();
			else if((module_list[j].name=="forces")&&(module_list[j].definition=="def"))
				def_forces();
			else if((module_list[j].name=="newton")&&(module_list[j].definition=="def"))
				def_newton();
		}
	//sizing module-variable array 'com_target3'
	sizing_arrays();

	// allocating memory for the com index arrays
	flat3_com_ind=new int[flat3_com_count];
	if(!flat3_com_count){cerr<<"*** Error: flat3_com_count[] allocation failed *** \n";system("pause");exit(1);}
	target_com_ind=new int[target_com_count];
	if(!target_com_count){cerr<<"*** Error: target_com_count[] allocation failed *** \n";system("pause");exit(1);}
	com_target3=new Variable[ncom_target3];
	if(!com_target3){cerr<<"*** Error: com_missile6[] allocation failed *** \n";system("pause");exit(1);}

	//building the index arrays of the data to be loaded into the packets of 'combus'
	com_index_arrays();

}
///////////////////////////////////////////////////////////////////////////////
//Destructor deallocating dynamic memory
//				  
//010205 Created by Peter H Zipfel
//011129 Adapted to SRAAM6 simulation, PZi
///////////////////////////////////////////////////////////////////////////////

Target::~Target()
{
	delete [] target;
	delete [] flat3;
	delete [] flat3_com_ind;
	delete [] target_com_ind;
	delete [] com_target3;
}

///////////////////////////////////////////////////////////////////////////////
//////////////////// Members of class 'Vehicle' ///////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//Constructor of class 'Vehicle'
//allocating dynamic memory for the array of pointers of type 'Cadac'
//and returning the pointer to array
//
//010626 Created by Peter H Zipfel
///////////////////////////////////////////////////////////////////////////////
Vehicle::Vehicle(int number)
{
	capacity=number;
	vehicle_ptr=new Cadac *[capacity];
	if(vehicle_ptr==0){cerr<<"*** Error:'vehicle_ptr' allocation failed *** \n";system("pause");exit(1);}
	howmany=0;
//	cerr<<">>> inside constructor of 'Vehicle' <<<\n";
}

///////////////////////////////////////////////////////////////////////////////
//Destructor of class 'Vehicle'
//de-allocating dynamic memory of the pointer-array of type 'Cadac'
//
//010626 Created by Peter H Zipfel
///////////////////////////////////////////////////////////////////////////////
Vehicle::~Vehicle()
{
//	cerr<<">>> inside destructor of 'Vehicle' <<<\n";
	delete [] vehicle_ptr;
}

///////////////////////////////////////////////////////////////////////////////
//Adding a vehicle pointer to the vehicle list
//
//010626 Created by Peter H Zipfel
///////////////////////////////////////////////////////////////////////////////
void Vehicle::add_vehicle(Cadac &pt)
{
	if(howmany<capacity)
		vehicle_ptr[howmany++]=&pt;			
}
///////////////////////////////////////////////////////////////////////////////
//Overloading operator [] so that it returns a 'Cadac' pointer
//
//010626 Created by Peter H Zipfel
///////////////////////////////////////////////////////////////////////////////
Cadac * Vehicle::operator[](int position)
{
	if(position>=0 && position<howmany)
		return vehicle_ptr[position];
	else
	{
		cout<<"*** Bad value: "<<position<<'\n';
		return 0;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Optaining size of vehicle list (total number of vehicles)
//
//010626 Created by Peter H Zipfel
///////////////////////////////////////////////////////////////////////////////
int Vehicle::size()
{
	return howmany;
}

