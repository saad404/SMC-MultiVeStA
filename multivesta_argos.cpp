#include "multivesta_argos.h"
#include "multivesta_loop_functions.h"
#include <argos3/core/simulator/simulator.h>
#include <argos3/core/utility/plugins/dynamic_loading.h>
#include <argos3/core/simulator/entity/positional_entity.h>

using namespace argos;

/****************************************/
/****************************************/

CSimulator* pcSimulator = NULL;
CMultiVeStALoopFunctions* pcLoopFunctions = NULL;

/****************************************/
/****************************************/

JNIEXPORT void JNICALL Java_multivesta_ARGoSState_initARGoS(JNIEnv* pc_env, jobject t_obj, jstring str_config_file) {
   /* Create the simulator instance */
   pcSimulator = &CSimulator::GetInstance();
   /* Load all ARGoS plug-ins */
   CDynamicLoading::LoadAllLibraries();
   /* Convert Java string to C string */
   const char* pchConfigFile = pc_env->GetStringUTFChars(str_config_file, 0);
   /* Set the experiment file name */
   pcSimulator->SetExperimentFileName(pchConfigFile);
   /* Release memory for C string */
   pc_env->ReleaseStringUTFChars(str_config_file, pchConfigFile);
   /* Load the file */
   pcSimulator->LoadExperiment();
   /* Get the reference to the loop functions */
   try {
      pcLoopFunctions = &dynamic_cast<CMultiVeStALoopFunctions&>(pcSimulator->GetLoopFunctions());
   }
   catch(std::bad_cast) {
      LOGERR << "[WARNING] The loop functions can't be cast to type CMultiVeStALoopFunctions - ignoring them" << std::endl;
   }
}

/****************************************/
/****************************************/

JNIEXPORT void JNICALL Java_multivesta_ARGoSState_destroyARGoS(JNIEnv* pc_env, jobject t_obj) {
   pcSimulator->Destroy();
   /* Unload all ARGoS plug-ins */
   CDynamicLoading::UnloadAllLibraries();
   LOG.Flush();
   LOGERR.Flush();
}

/****************************************/
/****************************************/

JNIEXPORT jdouble JNICALL Java_multivesta_ARGoSState_getTimeFromARGoS(JNIEnv* pc_env, jobject t_obj) {  
	 //return pcCoordinates->GetX();
	 return pcSimulator->GetSpace().GetSimulationClock();
}

/****************************************/
/****************************************/

JNIEXPORT void JNICALL Java_multivesta_ARGoSState_resetARGoS(JNIEnv* pc_env, jobject t_obj, jint n_random_seed) {
   pcSimulator->Reset(n_random_seed);
}

/****************************************/
/****************************************/

JNIEXPORT void JNICALL Java_multivesta_ARGoSState_stepARGoS(JNIEnv* pc_env, jobject t_obj) {
	pcSimulator->UpdateSpace();
}

/****************************************/
/****************************************/

JNIEXPORT void JNICALL Java_multivesta_ARGoSState_runARGoS(JNIEnv* pc_env, jobject t_obj) {
   pcSimulator->Execute();
}

/****************************************/
/****************************************/

JNIEXPORT jdouble JNICALL Java_multivesta_ARGoSState_observeARGoS__I(JNIEnv* pc_env, jobject t_obj, jint n_observation) {
   if(pcLoopFunctions != NULL) {
      return pcLoopFunctions->Observe(n_observation);
   }
   else {
      return 0.0f;
   }
}

/****************************************/
/****************************************/

JNIEXPORT jdouble JNICALL Java_multivesta_ARGoSState_observeARGoS__Ljava_lang_String_2(JNIEnv* pc_env, jobject t_obj, jstring obs) {
	// double x = CVector3().GetX();
	// CVector3().GetX();
	// Parse "fb1" and look for xpos / y pos.
	// "xpos(\"name\")" and "ypos(\"name\")" where name is the name of the entity
	// Take a look at footbot (battery enabled).
	//for (int i = 0 ; i < pcSimulator->GetSpace().GetEntityVector().size() ; i++) 
	//    std::cout << pcSimulator->GetSpace().GetEntityVector()[i] << std::endl;
	//std::cout << "x pos " << pcSimulator->GetSpace().GetEntityVector().front() << std::endl;
	//std::cout << "x pos " << CVector3().GetX() << std::endl;
	// This following line should work!!
	//std::cout << "x pos " << CPositionalEntity().GetPosition() << std::endl;	
	//double x = pcSimulator->GetSpace().GetEntityVector().front();
	return CVector3().GetX();
//	}
}

/****************************************/
/****************************************/

JNIEXPORT jboolean JNICALL Java_multivesta_ARGoSState_isExperimentFinishedInARGoS(JNIEnv* pc_env, jobject t_obj) {
   return pcSimulator->IsExperimentFinished();
}


