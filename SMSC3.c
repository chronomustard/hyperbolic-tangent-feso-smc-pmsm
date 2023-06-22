#define S_FUNCTION_LEVEL 2 
#define S_FUNCTION_NAME SMSC3
#include "simstruc.h" 
#include <math.h> 

#define U(element) (*uPtrs[element]) /*Pointer to Input Port0*/ 

static void mdlInitializeSizes(SimStruct *S){ 
	ssSetNumDiscStates(S, 3); // 3 STATE
	if (!ssSetNumInputPorts(S, 1)) return; 
	ssSetInputPortWidth(S, 0, 5); // 5 INPUT
	ssSetInputPortDirectFeedThrough(S, 0, 1); 
	ssSetInputPortOverWritable(S, 0, 1); 
	if (!ssSetNumOutputPorts(S, 1)) return; 
	ssSetOutputPortWidth(S, 0, 2); // 2 OUTPUT
	ssSetNumSampleTimes(S, 1); 

	ssSetOptions(S, (SS_OPTION_EXCEPTION_FREE_CODE 
	| SS_OPTION_DISCRETE_VALUED_OUTPUT));
} 

static void mdlInitializeSampleTimes(SimStruct *S){ 
	ssSetSampleTime(S, 0, 1e-5);  //Sampling time
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

    real_T control_signal, error;
    
	Y[0] = X[1]; //Output Isqr
    Y[1] = X[2]; //Sigma
} 

#define MDL_UPDATE 
static void mdlUpdate(SimStruct *S, int_T tid) {
	real_T *X = ssGetRealDiscStates(S); 
	InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0); 

	real_T dt = 1e-5; //Sampling time

    // PMSM MODEL PARAMETER
    real_T N    = 4;
    real_T psi  = 0.121;
    real_T Lsd  = 16.61e-3;
    real_T Lsq  = 16.22e-3;
    real_T Rs   = 0.55;
    real_T J    = 0.01;
    real_T B    = 0.08;
    
    // INPUT
    real_T omega_ref, omega_act, z2, mu_new;
    omega_ref = U(0);
    omega_act = U(1);
    z2 = U(2);
    
    
    real_T a, b, c, eps, k, eta, chi, gamma; 
    a = 0.5;
    b = 0.3;
    c = 15;
    eps = 10;
    k = 20;
    chi = (3 * N * N * psi) / (2 * J);
    eta = B / J;
    gamma = N / J;
    
    
	// SMC Parameters
	real_T speed_error;
	real_T c_omega_new = U(3);
	real_T gamma_new   = U(4); 
	
	real_T sigma, sgn_sigma;
	
	speed_error = omega_act - omega_ref;
	     
	// SMC State
	real_T error_itgr_old = X[0];
	
	// SMC State Integral
	real_T error_itgr     = error_itgr_old + speed_error*dt;
	
	// SMC State Update
	X[0] = error_itgr;
	
	// SMC Control Action
	sigma = speed_error + (c_omega_new*error_itgr);
	
	if(sigma > 0){
		sgn_sigma = 1;
	}
	else if(sigma < 0){
		sgn_sigma = -1;
	}
	else{
		sgn_sigma = 0;
	}
	
	mu_new = (1/chi)*(eta*fabs(omega_act) + c_omega_new*fabs(speed_error));
	
	real_T Isq_ref = -gamma_new*sigma - mu_new*sgn_sigma - (1/chi)*z2;
    
       	
	X[1] = Isq_ref;	
	X[2] = sigma;
}

static void mdlTerminate(SimStruct *S) 
{ } /*Keep this function empty since no memory is allocated*/ 

#ifdef MATLAB_MEX_FILE 
/* Is this file being compiled as a MEX-file? */ 
#include "simulink.c" /*MEX-file interface mechanism*/ 
#else 
#include "cg_sfun.h" /*Code generation registration function*/ 
#endif
