#define S_FUNCTION_LEVEL 2 
#define S_FUNCTION_NAME ESO_SMSC_VX
#include "simstruc.h" 
#include <math.h> 

#define U(element) (*uPtrs[element]) /*Pointer to Input Port0*/ 

static void mdlInitializeSizes(SimStruct *S){ 

	ssSetNumDiscStates(S, 2); 
	
	if (!ssSetNumInputPorts(S, 1)) return; 
	
	ssSetInputPortWidth(S, 0, 9);  //9 Input
	ssSetInputPortDirectFeedThrough(S, 0, 1); 
	ssSetInputPortOverWritable(S, 0, 1); 
	
	if (!ssSetNumOutputPorts(S, 1)) return; 
	
	ssSetOutputPortWidth(S, 0, 2); //2 Output
	ssSetNumSampleTimes(S, 1); 

	ssSetOptions(S, (SS_OPTION_EXCEPTION_FREE_CODE | SS_OPTION_DISCRETE_VALUED_OUTPUT));
	
} 

static void mdlInitializeSampleTimes(SimStruct *S){ 

	ssSetSampleTime(S, 0, 1e-5); 
	ssSetOffsetTime(S, 0, 0.0);
	
} 

#define MDL_INITIALIZE_CONDITIONS 
static void mdlInitializeConditions(SimStruct *S){ 

	real_T *X0 = ssGetRealDiscStates(S); 
	int_T nXStates = ssGetNumDiscStates(S); 
	InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0); 
	int_T i; 

	/* initialize the states to 0.0 */ 
	for (i=0; i < nXStates; i++) { 
		X0[i] = 0.0; 
	} 
	
} 

static void mdlOutputs(SimStruct *S, int_T tid){ 

	real_T *Y = ssGetOutputPortRealSignal(S,0); 
	real_T *X = ssGetRealDiscStates(S); 

	Y[0] = X[0]; // z1
	Y[1] = X[1]; // z2

} 

#define MDL_UPDATE 
static void mdlUpdate(SimStruct *S, int_T tid) { 

	real_T *X = ssGetRealDiscStates(S); 
	InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0); 

	real_T dt = 1e-5;
	
	// Inputs
	real_T omega_ref = U(0);
	real_T omega_act = U(1);
	real_T Ia        = U(2);
	real_T Ib        = U(3);
	real_T Ic        = U(4);
	real_T theta_e   = U(5); 
	
	real_T I_alpha, I_beta, Isq, Isd;
	
	real_T c = 0.816497; // sqrt(2/3) 
    real_T x = 0.866025; // sqrt(3)/2
	
	// Three-phase to Alpha-beta
	I_alpha = c*(Ia - 0.5*Ib - 0.5*Ic); 
    I_beta = c*(x*Ib - x*Ic);
	
	// Alpha-beta to DQ
	Isd = (I_alpha * cos(theta_e)) + (I_beta * sin(theta_e));
    Isq = (-I_alpha * sin(theta_e)) + (I_beta * cos(theta_e));  
	
	// ESO Parameters
	real_T est_error;
	real_T g, g_hat_dot, g_hat_old, g_hat, z1_dot, z2_dot, z1, z2;
	
	real_T chi, eta;
	real_T N  = 4.0;
	real_T psi = 0.175;
	real_T J0  = 0.01;
	real_T B0  = 0.01;
	
	chi = (3*N*N*psi)/(2*J0);
	eta = B0/J0;
	
	// ESO Tuning Parameters
	real_T beta_01_new = U(6);
	real_T beta_02_new = U(7);
    real_T beta_03_new = U(8);
		
	// ESO States
	real_T z1_old = X[0];
	real_T z2_old = X[1];
    	
	// ESO States Derivatives
    
    g = z1_dot - chi*Isq + z2;
    
    est_error = z1_old - omega_act;
    z1_dot = z2_old + g + chi*Isq - beta_01_new*est_error;
    z2_dot = - beta_02_new * tanh( beta_03_new * est_error );
	
	// ESO States Integral
    
    z1 = z1_old + z1_dot*dt; //Estimate Speed
    z2 = z2_old + z2_dot*dt; //Estimate Disturbance
   
		// ESO States Update
	X[0] = z1;
	X[1] = z2;
}

static void mdlTerminate(SimStruct *S) 
{ } /*Keep this function empty since no memory is allocated*/ 

#ifdef MATLAB_MEX_FILE 
/* Is this file being compiled as a MEX-file? */ 
#include "simulink.c" /*MEX-file interface mechanism*/ 
#else 
#include "cg_sfun.h" /*Code generation registration function*/ 
#endif
