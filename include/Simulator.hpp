#ifndef SIMULATOR_H
#define SIMULATOR_H

class Simulator;

#include "../include/Frame.hpp"
#include "../include/Renderer.hpp"
#include "../include/RayTracer.hpp"
#include "../include/BodyTracer.hpp"
#include "../include/Nbody.hpp"
#include "../include/Body.hpp"

#include <vector>

class Simulator{
	private:
		// Simulation data
		std::vector<Body*> *bodies;
		double time;
		double dt;
		int simulationSteps;

		// Frame for visualization
		Renderer *renderer;
		Frame *frame;
		
		// Sub renderers
		BodyTracer *bodyTracer;

		// Sub simulators
		Nbody *nbody;
		RayTracer *rayTracer;
	public:
		/**
		* Creates the simultor class for N-Body simulation
		**/
		Simulator(double time, double dt, std::vector<Body*> *bodies);
		
		/**
		* Finalizes the simulator
		**/
		~Simulator();
		
		/**
		* main entry point to simulate one time step
		**/
		void simulate(void);
		
		/**
		* Returns the time
		**/
		double getTime(void);
		
		/**
		* Returns the bodies
		**/
		std::vector<Body*>* getBodies(void);
		
		/**
		* Returns true if the user has pressed the ESC button, or clicked on the frame close button
		* resulting that the program finalizes
		**/
		bool isRunning(void);
		
		/**
		* Returns the pointer to the Nbody simulator
		**/
		Nbody* getNbodySimulator(void);
		
		/**
		* Returns the pointer to the RayTracer simulator
		**/
		RayTracer* getRayTracerSimulator(void);
		
		/**
		* Returns the pointer to the BodyTracer renderer
		**/
		BodyTracer* getBodyTracer(void);
};

#endif
