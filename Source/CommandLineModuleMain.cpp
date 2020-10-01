
#include <thread>
#include <string>
#include <iostream>
#include <chrono>

#include <amm_std.h>


#define DEFAULT_UUID_STR "00000000-0000-0000-0000-000000000000"
#define DEFAULT_STR "Command line test"


/// Is the main program in a loop?
bool isRunning = true;



/// Receiver for Assessment data.
///
/// @param a Assessment data.
/// @param SampleInfo_t FastRTPS sample info.
void OnNewAssessment (AMM::Assessment& a, eprosima::fastrtps::SampleInfo_t* info) {
   std::cout << "\nAssessment recieved!\n"
             << "ID:       " << a.id().id() << "\n"
             << "Event ID: " << a.event_id().id() << "\n"
             << "Value:    " << AMM::Utility::EAssessmentValueStr(a.value()) << "\n"
             << "Comment:  " << a.comment() << std::endl;
}

/// Receiver for Event Fragment data.
///
/// @param ef Event Fragment data.
/// @param SampleInfo_t FastRTPS sample info.
void OnNewEventFragment (AMM::EventFragment& ef, eprosima::fastrtps::SampleInfo_t* info) {
   std::cout << "\nEvent Fragment recieved!\n"
             << "ID:        " << ef.id().id() << "\n"
             << "Timestamp: " << ef.timestamp() << "\n"
             << "Encounter: " << ef.educational_encounter().id() << "\n"
             << "Location:  " << ef.location().name() << " - " << ef.location().FMAID() << "\n"
             << "Agent:     " << AMM::Utility::EEventAgentTypeStr(ef.agent_type()) << "\n"
             << "Agent ID:  " << ef.agent_id().id() << "\n"
             << "Type:      " << ef.type() << "\n"
             << "Data:      " << ef.data() << std::endl;
}

/// Receiver for Event Record data.
///
/// @param er Event Record data.
/// @param SampleInfo_t FastRTPS sample info.
void OnNewEventRecord (AMM::EventRecord& er, eprosima::fastrtps::SampleInfo_t* info) {
   std::cout << "\nEvent Record recieved!\n"
             << "ID:        " << er.id().id() << "\n"
             << "timestamp: " << er.timestamp() << "\n"
             << "Encounter: " << er.educational_encounter().id() << "\n"
             << "Location:  " << er.location().name() << " - " << er.location().FMAID() << "\n"
             << "Agent:     " << AMM::Utility::EEventAgentTypeStr(er.agent_type()) << "\n"
             << "Agent ID:  " << er.agent_id().id() << "\n"
             << "Type:      " << er.type() << "\n"
             << "Data:      " << er.data() << std::endl;
}

/// Receiver for Fragment Amendment Request data.
///
/// @param farq Fragment Amendment Request data.
/// @param SampleInfo_t FastRTPS sample info.
void OnNewFragmentAmendmentRequest (AMM::FragmentAmendmentRequest& farq, eprosima::fastrtps::SampleInfo_t* info) {
   std::cout << "\nFragment Amendment Request recieved!\n"
             << "ID:          " << farq.id().id() << "\n"
             << "Fragment ID: " << farq.fragment_id().id() << "\n"
             << "Status:      " << AMM::Utility::EFarStatusStr(farq.status()) << "\n"
             << "Location:    " << farq.location().name() << " - " << farq.location().FMAID() << "\n"
             << "Agent:       " << AMM::Utility::EEventAgentTypeStr(farq.agent_type()) << "\n"
             << "Agent ID:    " << farq.agent_id().id() << std::endl;
}

/// Receiver for Log data.
///
/// @param l Log data.
/// @param SampleInfo_t FastRTPS sample info.
void OnNewLog (AMM::Log& l, eprosima::fastrtps::SampleInfo_t* info) {
   std::cout << "\nLog recieved!\n"
             << "Timestamp: " << l.timestamp() << "\n"
             << "Module ID: " << l.module_id().id() << "\n"
             << "Level:     " << AMM::Utility::ELogLevelStr(l.level()) << "\n"
             << "Message:   " << l.message() << std::endl;
}

/// Receiver for Module Configuration data.
///
/// @param mc Module Configuration data.
/// @param SampleInfo_t FastRTPS sample info.
void OnNewModuleConfiguration (AMM::ModuleConfiguration& mc, eprosima::fastrtps::SampleInfo_t* info) {
   std::cout << "\nModule Configuration recieved!\n"
             << "Name:         " << mc.name() << "\n"
             << "Module ID:    " << mc.module_id().id() << "\n"
             << "Encounter:    " << mc.educational_encounter().id() << "\n"
             << "Timestamp:    " << mc.timestamp() << "\n"
             << "Capabilities: Not shown" << std::endl;
}

/// Receiver for Omitted Event data.
///
/// @param oe Omitted Event data.
/// @param SampleInfo_t FastRTPS sample info.
void OnNewOmittedEvent (AMM::OmittedEvent& oe, eprosima::fastrtps::SampleInfo_t* info) {
   std::cout << "\nOmitted Event recieved!\n"
             << "ID:        " << oe.id().id() << "\n"
             << "timestamp: " << oe.timestamp() << "\n"
             << "Encounter: " << oe.educational_encounter().id() << "\n"
             << "Location:  " << oe.location().name() << " - " << oe.location().FMAID() << "\n"
             << "Agent:     " << AMM::Utility::EEventAgentTypeStr(oe.agent_type()) << "\n"
             << "Agent ID:  " << oe.agent_id().id() << "\n"
             << "Type:      " << oe.type() << "\n"
             << "Data:      " << oe.data() << std::endl;
}

/// Receiver for Operational Description data.
///
/// @param od Operational Description data.
/// @param SampleInfo_t FastRTPS sample info.
void OnNewOperationalDescription (AMM::OperationalDescription& od, eprosima::fastrtps::SampleInfo_t* info) {
   std::cout << "\nOperational Description recieved!\n"
             << "Name:         " << od.name() << "\n"
             << "Description:  " << od.description() << "\n"
             << "Manufacturer: " << od.manufacturer() << "\n"
             << "Module:       " << od.model() << "\n"
             << "Serial:       " << od.serial_number() << "\n"
             << "Module ID:    " << od.module_id().id() << "\n"
             << "Module Ver:   " << od.module_version() << "\n"
             << "Config Ver:   " << od.configuration_version() << "\n"
             << "AMM Version:  " << od.AMM_version() << "\n"
             << "IP Addresses: Not shown" << "\n"
             << "Capabilities: Not shown" << std::endl;

}

/// Receiver for Physiology Modification data.
///
/// @param pm Physiology Modification data.
/// @param SampleInfo_t FastRTPS sample info.
void OnNewPhysiologyModification (AMM::PhysiologyModification& pm, eprosima::fastrtps::SampleInfo_t* info) {
   std::cout << "\nPhysiology Modification recieved!\n"
             << "ID:       " << pm.id().id() << "\n"
             << "Event ID: " << pm.event_id().id() << "\n"
             << "Type:     " << pm.type() << "\n"
             << "Data:     " << pm.data() << std::endl;
}

/// Receiver for Physiology Value data.
///
/// @param pv Physiology Value data.
/// @param SampleInfo_t FastRTPS sample info.
void OnNewPhysiologyValue (AMM::PhysiologyValue& pv, eprosima::fastrtps::SampleInfo_t* info) {
   std::cout << "\nPhysiology Value recieved!\n"
             << "Encounter: " << pv.educational_encounter().id() << "\n"
             << "Sim Time:  " << pv.simulation_time() << "\n"
             << "Timestamp: " << pv.timestamp() << "\n"
             << "Name:      " << pv.name() << "\n"
             << "Unit:      " << pv.unit() << "\n"
             << "Value:     " << pv.value() << std::endl;
}

/// Receiver for Physiology Waveform data.
///
/// @param pw Physiology Waveform data.
/// @param SampleInfo_t FastRTPS sample info.
void OnNewPhysiologyWaveform (AMM::PhysiologyWaveform& pw, eprosima::fastrtps::SampleInfo_t* info) {
   std::cout << "\nPhysiology Waveform recieved!\n"
             << "Encounter: " << pw.educational_encounter().id() << "\n"
             << "Sim Time:  " << pw.simulation_time() << "\n"
             << "Timestamp: " << pw.timestamp() << "\n"
             << "Name:      " << pw.name() << "\n"
             << "Unit:      " << pw.unit() << "\n"
             << "Value:     " << pw.value() << std::endl;
}

/// Receiver for Render Modification data.
///
/// @param rm Render Modification data.
/// @param SampleInfo_t FastRTPS sample info.
void OnNewRenderModification (AMM::RenderModification& rm, eprosima::fastrtps::SampleInfo_t* info) {
   std::cout << "\nRender Modification recieved!\n"
             << "ID:       " << rm.id().id() << "\n"
             << "Event ID: " << rm.event_id().id() << "\n"
             << "Type:     " << rm.type() << "\n"
             << "Data      " << rm.data() << std::endl;
}

/// Receiver for Simulation Control data.
///
/// @param sc Simulation Control data.
/// @param SampleInfo_t FastRTPS sample info.
void OnNewSimulationControl (AMM::SimulationControl& sc, eprosima::fastrtps::SampleInfo_t* info) {
   std::cout << "\nSimulation Control recieved!\n"
             << "Timestamp: " << sc.timestamp() << "\n"
             << "Type:      " << AMM::Utility::EControlTypeStr(sc.type()) << "\n"
             << "Encounter: " << sc.educational_encounter().id() << std::endl;
}

/// Receiver for Status data.
///
/// @param ss Status data.
/// @param SampleInfo_t FastRTPS sample info.
void OnNewStatus (AMM::Status& s, eprosima::fastrtps::SampleInfo_t* info) {
   std::cout << "\nStatus recieved!\n"
             << "Module ID:   " << s.module_id().id() << "\n"
             << "Module Name: " << s.module_name() << "\n"
             << "Encounter:   " << s.educational_encounter().id() << "\n"
             << "Capability:  Not shown" << "\n"
             << "Timestamp:   " << s.timestamp() << "\n"
             << "Value:       " << AMM::Utility::EStatusValueStr(s.value()) << "\n"
             << "Message:     " << s.message() << std::endl;
}

/// Receiver for Tick data.
///
/// @param t Tick data.
/// @param SampleInfo_t FastRTPS sample info.
void OnNewTick (AMM::Tick& t, eprosima::fastrtps::SampleInfo_t* info) {
   std::cout << "\nTick recieved!\n"
             << "Frame: " << t.frame() << "\n"
             << "Time:  " << t.time() << std::endl;
}

/// Receiver for Instrument Data data.
///
/// @param d Instrument Data data.
/// @param SampleInfo_t FastRTPS sample info.
void OnNewInstrumentData (AMM::InstrumentData& d, eprosima::fastrtps::SampleInfo_t* info) {
   std::cout << "\nInstrument Data recieved!\n"
             << "Instrument: " << d.instrument() << "\n"
             << "Payload:    " << d.payload() << std::endl;
}

/// Receiver for Command data.
///
/// @param c Command data.
/// @param SampleInfo_t FastRTPS sample info.
void OnNewCommand (AMM::Command& c, eprosima::fastrtps::SampleInfo_t* info) {
   std::cout << "\nCommand recieved!\n"
             << "Message:" << c.message() << std::endl;
}



/// User prompt for selecting Assessment Value.
///
/// Prompts the user to select any of the given Assessment Values.
/// @returns The user selected enum value for Assessment Value.
AMM::AssessmentValue UserSelectAssessmentValue () {

   for (;;) {
      std::cout << " Select Assessment Value:\n"
                << "   [1] Omission Error\n"
                << "   [2] Commission Error\n"
                << "   [3] Execution Error\n"
                << "   [4] Success\n"
                << " >> ";

      std::string action;
      std::getline(std::cin, action);

      if      (action == "1") return AMM::AssessmentValue::OMISSION_ERROR;
      else if (action == "2") return AMM::AssessmentValue::COMMISSION_ERROR;
      else if (action == "3") return AMM::AssessmentValue::EXECUTION_ERROR;
      else if (action == "4") return AMM::AssessmentValue::SUCCESS;
      else    std::cout << "Invalid option!\n";
   }
}

/// User prompt for selecting Event Agent Type.
///
/// Prompts the user to select any of the given Event Agent Types.
/// @returns The user selected enum value for Event Agent Type.
AMM::EventAgentType UserSelectAgentType () {

   for (;;) {
      std::cout << " Select Event Agent Type:\n"
                << "   [1] Learner\n"
                << "   [2] Instructor\n"
                << "   [3] Scenario\n"
                << "   [4] Physiology\n"
                << " >> ";

      std::string action;
      std::getline(std::cin, action);

      if      (action == "1") return AMM::EventAgentType::LEARNER;
      else if (action == "2") return AMM::EventAgentType::INSTRUCTOR;
      else if (action == "3") return AMM::EventAgentType::SCENARIO;
      else if (action == "4") return AMM::EventAgentType::PHYSIOLOGY;
      else    std::cout << "Invalid option!\n";
   }
}

/// User prompt for selected FAR Status.
///
/// Prompts the user to select any of the given FAR Statuses.
/// @returns The user selected enum value for FAR Status.
AMM::FAR_Status UserSelectFarStatus () {

   for (;;) {
      std::cout << " Select Event Agent Type:\n"
                << "   [1] Requesting\n"
                << "   [2] Accetped\n"
                << "   [3] Rejected\n"
                << " >> ";

      std::string action;
      std::getline(std::cin, action);

      if      (action == "1") return AMM::FAR_Status::REQUESTING;
      else if (action == "2") return AMM::FAR_Status::ACCEPTED;
      else if (action == "3") return AMM::FAR_Status::REJECTED;
      else    std::cout << "Invalid option!\n";
   }
}

/// User prompt for selected Log Level
///
/// Prompts the user to select any of the given Log Levels.
/// @returns The user selected enum value for Log Level
AMM::LogLevel UserSelectLogLevel () {

   for (;;) {
      std::cout << " Select Log Level:\n"
                << "   [1] Fatal\n"
                << "   [2] Error\n"
                << "   [3] Warning\n"
                << "   [4] Info\n"
                << "   [5] Debug\n"
                << "   [6] Trace\n"
                << " >> ";

      std::string action;
      std::getline(std::cin, action);

      if      (action == "1") return AMM::LogLevel::L_FATAL;
      else if (action == "2") return AMM::LogLevel::L_ERROR;
      else if (action == "3") return AMM::LogLevel::L_WARN;
      else if (action == "4") return AMM::LogLevel::L_INFO;
      else if (action == "5") return AMM::LogLevel::L_DEBUG;
      else if (action == "6") return AMM::LogLevel::L_TRACE;
      else    std::cout << "Invalid option!\n";
   }
}

/// User prompt for selected Control Type.
///
/// Prompts the user to select any of the given Control Types.
/// @returns The user selected enum value for Control Type.
AMM::ControlType UserSelectControlType () {

   for (;;) {
      std::cout << " Select Simulation Control:\n"
                << "   [1] Run\n"
                << "   [2] Halt\n"
                << "   [3] Reset\n"
                << "   [4] Save\n"
                << " >> ";

      std::string action;
      std::getline(std::cin, action);

      if      (action == "1") return AMM::ControlType::RUN;
      else if (action == "2") return AMM::ControlType::HALT;
      else if (action == "3") return AMM::ControlType::RESET;
      else if (action == "4") return AMM::ControlType::SAVE;
      else    std::cout << "Invalid option!\n";
   }
}

/// User prompt for selected Status Value.
///
/// Prompts the user to select any of the given Status Values.
/// @returns The user selected enum value for Status Value.
AMM::StatusValue UserSelectStatusValue () {

   for (;;) {
      std::cout << " Select Status Value:\n"
                << "   [1] Operational\n"
                << "   [2] Inoperative\n"
                << "   [3] Exigent\n"
                << " >> ";

      std::string action;
      std::getline(std::cin, action);

      if      (action == "1") return AMM::StatusValue::OPERATIONAL;
      else if (action == "2") return AMM::StatusValue::INOPERATIVE;
      else if (action == "3") return AMM::StatusValue::EXIGENT;
      else    std::cout << "Invalid option!\n";
   }
}



/// Publishes Assessment data.
///
/// @param mgr Instance of DDS Manager to call Write Assessment.
int PublishAssessment (AMM::DDSManager<void>* mgr) {

   std::string errmsg;

   if (mgr->CreateAssessmentPublisher(errmsg) != 0) {
      std::cout << errmsg << std::endl;
      return 1;
   }

   AMM::UUID uuid;
   uuid.id(DEFAULT_UUID_STR);

   AMM::Assessment ass;
   ass.id(uuid);
   ass.event_id(uuid);
   ass.value(UserSelectAssessmentValue());
   ass.comment(DEFAULT_STR);

   std::cout << " Writing Assessment topic.\n" << std::endl;

   std::this_thread::sleep_for(std::chrono::milliseconds(100));

   if (mgr->WriteAssessment(errmsg, ass) != 0) {
      std::cout << errmsg << std::endl;
   }

   return 0;
}

/// Publishes Event Fragment data.
///
/// @param mgr Instance of DDS Manager to call Write Event Fragment.
int PublishEventFragment (AMM::DDSManager<void>* mgr) {

   std::string errmsg;

   if (mgr->CreateEventFragmentPublisher(errmsg) != 0) {
      std::cout << errmsg << std::endl;
      return 1;
   }

   using namespace std::chrono;
   auto timestamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

   AMM::UUID uuid;
   uuid.id(DEFAULT_UUID_STR);


   AMM::FMA_Location location;
   location.FMAID(0);
   location.name(DEFAULT_STR);


   AMM::EventFragment eventFrag;
   eventFrag.id(uuid);
   eventFrag.timestamp(timestamp);
   eventFrag.educational_encounter(uuid);
   eventFrag.location(location);
   eventFrag.agent_type(UserSelectAgentType());
   eventFrag.agent_id(uuid);
   eventFrag.type(DEFAULT_STR);
   eventFrag.data(DEFAULT_STR);


   std::cout << " Writing Event Fragment topic.\n" << std::endl;

   std::this_thread::sleep_for(std::chrono::milliseconds(100));

   if (mgr->WriteEventFragment(errmsg, eventFrag) != 0) {
      std::cout << errmsg << std::endl;
   }

   return 0;
}

/// Publishes Event Record data.
///
/// @param mgr Instance of DDS Manager to call Write Event Record.
int PublishEventRecord (AMM::DDSManager<void>* mgr) {

   std::string errmsg;

   if (mgr->CreateEventRecordPublisher(errmsg) != 0) {
      std::cout << errmsg << std::endl;
      return 1;
   }

   using namespace std::chrono;
   auto timestamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

   AMM::UUID uuid;
   uuid.id(DEFAULT_UUID_STR);


   AMM::FMA_Location location;
   location.FMAID(0);
   location.name(DEFAULT_STR);


   AMM::EventRecord eventRec;
   eventRec.id(uuid);
   eventRec.timestamp(timestamp);
   eventRec.educational_encounter(uuid);
   eventRec.location(location);
   eventRec.agent_type(UserSelectAgentType());
   eventRec.type(DEFAULT_STR);
   eventRec.data(DEFAULT_STR);


   std::cout << " Writing Event Record.\n" << std::endl;

   std::this_thread::sleep_for(std::chrono::milliseconds(100));

   if (mgr->WriteEventRecord(errmsg, eventRec) != 0) {
      std::cout << errmsg << std::endl;
   }

   return 0;
}

/// Publishes Fragment Amendment Request data.
///
/// @param mgr Instance of DDS Manager to call Write Fragment Amendment Request.
int PublishFar (AMM::DDSManager<void>* mgr) {

   std::string errmsg;

   if (mgr->CreateFragmentAmendmentRequestPublisher(errmsg) != 0) {
      std::cout << errmsg << std::endl;
      return 1;
   }

   AMM::FMA_Location location;
   location.FMAID(0);
   location.name(DEFAULT_STR);

   AMM::UUID uuid;
   uuid.id(DEFAULT_UUID_STR);

   AMM::FragmentAmendmentRequest ffar;
   ffar.id(uuid);
   ffar.fragment_id(uuid);
   ffar.status(UserSelectFarStatus());
   ffar.location(location);
   ffar.agent_type(UserSelectAgentType());
   ffar.agent_id(uuid);


   std::cout << " Writing Fragment Amendment Request topic.\n" << std::endl;

   std::this_thread::sleep_for(std::chrono::milliseconds(100));

   if (mgr->WriteFragmentAmendmentRequest(errmsg, ffar) != 0) {
      std::cout << errmsg << std::endl;
   }

   return 0;
}

/// Publishes Log data.
///
/// @param mgr Instance of DDS Manager to call Write Log.
int PublishLog (AMM::DDSManager<void>* mgr) {

   std::string errmsg;

   if (mgr->CreateLogPublisher(errmsg) != 0) {
      std::cout << errmsg << std::endl;
      return 1;
   }

   using namespace std::chrono;
   auto timestamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

   AMM::UUID uuid;
   uuid.id(DEFAULT_UUID_STR);

   AMM::Log log;
   log.timestamp(timestamp);
   log.module_id(uuid);
   log.level(UserSelectLogLevel());
   log.message(DEFAULT_STR);


   std::cout << " Writing Log topic.\n";

   std::this_thread::sleep_for(std::chrono::milliseconds(100));

   if (mgr->WriteLog(errmsg, log) != 0) {
      std::cout << errmsg << std::endl;
   }

   return 0;
}

/// Publishes Module Config data.
///
/// @param mgr Instance of DDS Manager to call Write Module Config.
int PublishModuleConfig (AMM::DDSManager<void>* mgr) {

   std::string errmsg;

   if (mgr->CreateModuleConfigurationPublisher(errmsg) != 0) {
      std::cout << errmsg << std::endl;
      return 1;
   }

   using namespace std::chrono;
   auto timestamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

   AMM::UUID uuid;
   uuid.id(DEFAULT_UUID_STR);


   AMM::ModuleConfiguration modConfig;
   modConfig.name(DEFAULT_STR);
   modConfig.module_id(uuid);
   modConfig.educational_encounter(uuid);
   modConfig.timestamp(timestamp);
   modConfig.capabilities_configuration(DEFAULT_STR);


   std::cout << " Writing Module Configuration.\n" << std::endl;

   std::this_thread::sleep_for(std::chrono::milliseconds(100));

   if (mgr->WriteModuleConfiguration(errmsg, modConfig) != 0) {
      std::cout << errmsg << std::endl;
   }

   return 0;
}

/// Publishes Omitted Event data.
///
/// @param mgr Instance of DDS Manager to call Write Omitted Event.
int PublishOmittedEvent (AMM::DDSManager<void>* mgr) {

   std::string errmsg;

   if (mgr->CreateOmittedEventPublisher(errmsg) != 0) {
      std::cout << errmsg << std::endl;
      return 1;
   }

   using namespace std::chrono;
   auto timestamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

   AMM::UUID uuid;
   uuid.id(DEFAULT_UUID_STR);


   AMM::FMA_Location location;
   location.FMAID(0);
   location.name(DEFAULT_STR);


   AMM::OmittedEvent omittedEvent;
   omittedEvent.id(uuid);
   omittedEvent.timestamp(timestamp);
   omittedEvent.educational_encounter(uuid);
   omittedEvent.location(location);
   omittedEvent.agent_type(UserSelectAgentType());
   omittedEvent.agent_id(uuid);
   omittedEvent.type(DEFAULT_STR);
   omittedEvent.data(DEFAULT_STR);


   std::cout << " Writing Omitted Event topic.\n" << std::endl;

   std::this_thread::sleep_for(std::chrono::milliseconds(100));

   if (mgr->WriteOmittedEvent(errmsg, omittedEvent) != 0) {
      std::cout << errmsg << std::endl;
   }

   return 0;
}

/// Publishes Operational Description data.
///
/// @param mgr Instance of DDS Manager to call Write Operational Description.
int PublishOperationalDescription (AMM::DDSManager<void>* mgr) {

   std::string errmsg;

   if (mgr->CreateOperationalDescriptionPublisher(errmsg) != 0) {
      std::cout << errmsg << std::endl;
      return 1;
   }

   AMM::Semantic_Version version;
   version.major(1);
   version.minor(0);
   version.patch(0);

   AMM::UUID uuid;
   uuid.id(DEFAULT_UUID_STR);

   AMM::OperationalDescription opDescript;
   opDescript.name(DEFAULT_STR);
   opDescript.description(DEFAULT_STR);
   opDescript.manufacturer(DEFAULT_STR);
   opDescript.model(DEFAULT_STR);
   opDescript.serial_number(DEFAULT_STR);
   opDescript.module_id(uuid);
   opDescript.module_version(DEFAULT_STR);
   // opDescript.configuration_version(version);
   // opDescript.AMM_version(version);


   std::cout << " Writing Operational Description topic.\n" << std::endl;

   std::this_thread::sleep_for(std::chrono::milliseconds(100));

   if (mgr->WriteOperationalDescription(errmsg, opDescript) != 0) {
      std::cout << errmsg << std::endl;
   }

   return 0;
}

/// Publishes Physiology Modification data.
///
/// @param mgr Instance of DDS Manager to call Write Physiology Modification.
int PublishPhysiologyModification (AMM::DDSManager<void>* mgr) {

   std::string errmsg;

   if (mgr->CreatePhysiologyModificationPublisher(errmsg) != 0) {
      std::cout << errmsg << std::endl;
      return 1;
   }

   AMM::UUID uuid;
   uuid.id(DEFAULT_UUID_STR);

   AMM::PhysiologyModification physMod;
   physMod.id(uuid);
   physMod.event_id(uuid);
   physMod.type(DEFAULT_STR);
   physMod.data(DEFAULT_STR);


   std::cout << " Writing Physiology Modification topic test.\n" << std::endl;

   std::this_thread::sleep_for(std::chrono::milliseconds(100));

   if (mgr->WritePhysiologyModification(errmsg, physMod) != 0) {
      std::cout << errmsg << std::endl;
   }


   return 0;
}

/// Publishes Physiology Value data.
///
/// @param mgr Instance of DDS Manager to call Write Physiology Value.
int PublishPhysiologyValue (AMM::DDSManager<void>* mgr) {

   std::string errmsg;

   if (mgr->CreatePhysiologyValuePublisher(errmsg) != 0) {
      std::cout << errmsg << std::endl;
      return 1;
   }

   using namespace std::chrono;
   auto timestamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

   AMM::UUID uuid;
   uuid.id(DEFAULT_UUID_STR);

   AMM::PhysiologyValue physValue;
   physValue.educational_encounter(uuid);
   physValue.simulation_time(0);
   physValue.timestamp(timestamp);
   physValue.name(DEFAULT_STR);
   physValue.unit(DEFAULT_STR);
   physValue.value(0);


   std::cout << " Writing Physiology Value topic.\n" << std::endl;

   std::this_thread::sleep_for(std::chrono::milliseconds(100));

   if (mgr->WritePhysiologyValue(errmsg, physValue) != 0) {
      std::cout << errmsg << std::endl;
   }

   return 0;
}

/// Publishes Physiology Waveform data.
///
/// @param mgr Instance of DDS Manager to call Write Physiology Waveform.
int PublishPhysiologyWaveform (AMM::DDSManager<void>* mgr) {

   std::string errmsg;

   if (mgr->CreatePhysiologyWaveformPublisher(errmsg) != 0) {
      std::cout << errmsg << std::endl;
      return 1;
   }

   using namespace std::chrono;
   auto timestamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

   AMM::UUID uuid;
   uuid.id(DEFAULT_UUID_STR);

   AMM::PhysiologyWaveform physWave;
   physWave.educational_encounter(uuid);
   physWave.simulation_time(0);
   physWave.timestamp(timestamp);
   physWave.name(DEFAULT_STR);
   physWave.unit(DEFAULT_STR);
   physWave.value(0);


   std::cout << " Writing Physiology Waveform topic.\n" << std::endl;

   std::this_thread::sleep_for(std::chrono::milliseconds(100));

   if (mgr->WritePhysiologyWaveform(errmsg, physWave) != 0) {
      std::cout << errmsg << std::endl;
   }

   return 0;
}

/// Publishes Assessment data.
///
/// @param mgr Instance of DDS Manager to call Write Assessment.
int PublishRenderModification (AMM::DDSManager<void>* mgr) {

   std::string errmsg;

   if (mgr->CreateRenderModificationPublisher(errmsg) != 0) {
      std::cout << errmsg << std::endl;
   }

   AMM::UUID uuid;
   uuid.id(DEFAULT_UUID_STR);

   AMM::RenderModification renderMod;
   renderMod.id(uuid);
   renderMod.event_id(uuid);
   renderMod.type(DEFAULT_STR);
   renderMod.data(DEFAULT_STR);

   std::cout << " Writing Render Modification topic.\n" << std::endl;

   std::this_thread::sleep_for(std::chrono::milliseconds(100));

   if (mgr->WriteRenderModification(errmsg, renderMod) != 0) {
      std::cout << errmsg << std::endl;
   }

   return 0;
}

/// Publishes Simulation Control data.
///
/// @param mgr Instance of DDS Manager to call Write Simulation Control.
int PublishSimControl (AMM::DDSManager<void>* mgr) {

   std::string errmsg;

   if (mgr->CreateSimulationControlPublisher(errmsg) != 0) {
      std::cout << errmsg << std::endl;
      return 1;
   }

   using namespace std::chrono;
   auto timestamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

   AMM::UUID uuid;
   uuid.id(DEFAULT_UUID_STR);

   AMM::SimulationControl simControl;
   simControl.timestamp(timestamp);
   simControl.type(UserSelectControlType());
   simControl.educational_encounter(uuid);

   std::cout << " Writing Simulation Control topic.\n" << std::endl;

   std::this_thread::sleep_for(std::chrono::milliseconds(100));

   if (mgr->WriteSimulationControl(errmsg, simControl) != 0) {
      std::cout << errmsg << std::endl;
   }

   return 0;
}

/// Publishes Status data.
///
/// @param mgr Instance of DDS Manager to call Write Status.
int PublishStatus (AMM::DDSManager<void>* mgr) {

   std::string errmsg;

   if (mgr->CreateStatusPublisher(errmsg) != 0) {
      std::cout << errmsg << std::endl;
      return 1;
   }

   using namespace std::chrono;
   auto timestamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

   AMM::UUID uuid;
   uuid.id(DEFAULT_UUID_STR);

   AMM::Status status;
   status.module_id(uuid);
   status.module_name(DEFAULT_STR);
   status.educational_encounter(uuid);
   status.capability(DEFAULT_STR);
   status.timestamp(timestamp);
   status.value(UserSelectStatusValue());
   status.message(DEFAULT_STR);

   std::cout << " Writing Status topic.\n" << std::endl;

   std::this_thread::sleep_for(std::chrono::milliseconds(100));

   if (mgr->WriteStatus(errmsg, status) != 0) {
      std::cout << errmsg << std::endl;
   }

   return 0;
}

/// Publishes Tick data.
///
/// @param mgr Instance of DDS Manager to call Write Tick.
int PublishTick (AMM::DDSManager<void>* mgr) {

   std::string errmsg;

   if (mgr->CreateTickPublisher(errmsg) != 0) {
      std::cout << errmsg << std::endl;
      return 1;
   }

   AMM::Tick t;
   t.frame(0);
   t.time(0);

   std::cout << " Writing Tick topic.\n" << std::endl;

   std::this_thread::sleep_for(std::chrono::milliseconds(100));

   if (mgr->WriteTick(errmsg, t) != 0) {
      std::cout << errmsg << std::endl;
   }

   return 0;
}

/// Publishes Instrument Data data.
///
/// @param mgr Instance of DDS Manager to call Write Instrument Data.
int PublishInstrumentData (AMM::DDSManager<void>* mgr) {

   std::string errmsg;

   if (mgr->CreateInstrumentDataPublisher(errmsg) != 0) {
      std::cout << errmsg << std::endl;
      return 1;
   }

   AMM::InstrumentData d;
   d.instrument(DEFAULT_STR);
   d.payload(DEFAULT_STR);

   std::cout << " Writing Instrument Data topic.\n" << std::endl;

   std::this_thread::sleep_for(std::chrono::milliseconds(100));

   if (mgr->WriteInstrumentData(errmsg, d) != 0) {
      std::cout << errmsg << std::endl;
   }

   return 0;
}

/// Publishes Command data.
///
/// @param mgr Instance of DDS Manager to call Write Command.
int PublishCommand (AMM::DDSManager<void>* mgr) {

   std::string errmsg;

   if (mgr->CreateCommandPublisher(errmsg) != 0) {
      std::cout << errmsg << std::endl;
      return 1;
   }

   AMM::Command c;
   c.message(DEFAULT_STR);

   std::cout << " Writing Command topic.\n" << std::endl;

   std::this_thread::sleep_for(std::chrono::milliseconds(100));

   if (mgr->WriteCommand(errmsg, c) != 0) {
      std::cout << errmsg << std::endl;
   }


   return 0;

}



/// Activate listening mode and display all incomming data.
///
/// Initializes ALL topic subscribers and displays their incomming data.
/// @note Intended for unit testing and controlled diagnostics.
/// Listening to a fully operational sim will result in lots os spam and noisey data.
/// @param Instance of DDS Manager to initialize subscribers.
int EnterListeningMode (AMM::DDSManager<void>* mgr) {

   std::string errmsg;

   if (mgr->CreateAssessmentSubscriber(errmsg, &OnNewAssessment) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->CreateEventFragmentSubscriber(errmsg, &OnNewEventFragment) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->CreateEventRecordSubscriber(errmsg, &OnNewEventRecord) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->CreateFragmentAmendmentRequestSubscriber(errmsg, &OnNewFragmentAmendmentRequest) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->CreateLogSubscriber(errmsg, &OnNewLog) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->CreateModuleConfigurationSubscriber(errmsg, &OnNewModuleConfiguration) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->CreateOmittedEventSubscriber(errmsg, &OnNewOmittedEvent) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->CreateOperationalDescriptionSubscriber(errmsg, &OnNewOperationalDescription) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->CreatePhysiologyModificationSubscriber(errmsg, &OnNewPhysiologyModification) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->CreatePhysiologyValueSubscriber(errmsg, &OnNewPhysiologyValue) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->CreatePhysiologyWaveformSubscriber(errmsg, &OnNewPhysiologyWaveform) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->CreateRenderModificationSubscriber(errmsg, &OnNewRenderModification) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->CreateSimulationControlSubscriber(errmsg, &OnNewSimulationControl) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->CreateStatusSubscriber(errmsg, &OnNewStatus) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->CreateTickSubscriber(errmsg, &OnNewTick) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->CreateInstrumentDataSubscriber(errmsg, &OnNewInstrumentData) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->CreateCommandSubscriber(errmsg, &OnNewCommand) != 0) {
      std::cout << errmsg << std::endl;
   }


   bool isListening = true;

   auto loop = [&]() {
      for (;;) {
         if (!isListening) break;
      }
   };

   std::thread t(loop);

   std::cout << "Listening for data. Press return to exit." << std::endl;
   std::cin.get();

   isListening = false;

   t.join();

   mgr->RemoveAssessmentSubscriber();
   mgr->RemoveEventFragmentSubscriber();
   mgr->RemoveEventRecordSubscriber();
   mgr->RemoveFragmentAmendmentRequestSubscriber();
   mgr->RemoveLogSubscriber();
   mgr->RemoveModuleConfigurationSubscriber();
   mgr->RemoveOmittedEventSubscriber();
   mgr->RemoveOperationalDescriptionSubscriber();
   mgr->RemovePhysiologyModificationSubscriber();
   mgr->RemovePhysiologyValueSubscriber();
   mgr->RemovePhysiologyWaveformSubscriber();
   mgr->RemoveRenderModificationSubscriber();
   mgr->RemoveSimulationControlSubscriber();
   mgr->RemoveStatusSubscriber();
   mgr->RemoveTickSubscriber();
   mgr->RemoveInstrumentDataSubscriber();
   mgr->RemoveCommandSubscriber();

   return 0;
}


/// Central program loop prompting for user action.
///
/// @param Instance of DDS Manager that will be passed along where necessary.
/// Is initialized in main.
void Menu (AMM::DDSManager<void>* mgr) {

   // Slight pause so other logging info is displayed before the menu.
   std::this_thread::sleep_for(std::chrono::milliseconds(100));

   std::cout << "\n"
      " [1]  Publish Assessment Topic\n"
      " [2]  Publish Event Fragment Topic\n"
      " [3]  Publish Event Record Topic\n"
      " [4]  Publish Fragment Amendment Request Topic\n"
      " [5]  Publish Log Topic\n"
      " [6]  Publish Module Config\n"
      " [7]  Publish Omitted Event Topic\n"
      " [8]  Publish Operational Description Topic\n"
      " [9]  Publish Physiology Modification Topic\n"
      " [10] Publish Physiology Value Topic\n"
      " [11] Publish Physiology Waveform Topic\n"
      " [12] Publish Render Modification Topic\n"
      " [13] Publish Sim Control Topic\n"
      " [14] Publish Status Topic\n"
      " [15] Publish Tick Topic\n"
      " [16] Publish Instrument Data Topic\n"
      " [17] Publish Command Topic\n"
      " ----\n"
      " [30] Enter Listening Mode\n"
      " ----\n"
      " [99] Shutdown\n"
      " ----\n"
   " >> ";

   std::string action;
   std::getline(std::cin, action);

   // Topic Menus
   if      (action == "1")  PublishAssessment(mgr);
   else if (action == "2")  PublishEventFragment(mgr);
   else if (action == "3")  PublishEventRecord(mgr);
   else if (action == "4")  PublishFar(mgr);
   else if (action == "5")  PublishLog(mgr);
   else if (action == "6")  PublishModuleConfig(mgr);
   else if (action == "7")  PublishOmittedEvent(mgr);
   else if (action == "8")  PublishOperationalDescription(mgr);
   else if (action == "9")  PublishPhysiologyModification(mgr);
   else if (action == "10") PublishPhysiologyValue(mgr);
   else if (action == "11") PublishPhysiologyWaveform(mgr);
   else if (action == "12") PublishRenderModification(mgr);
   else if (action == "13") PublishSimControl(mgr);
   else if (action == "14") PublishStatus(mgr);
   else if (action == "15") PublishTick(mgr);
   else if (action == "16") PublishInstrumentData(mgr);
   else if (action == "17") PublishCommand(mgr);

   // Listening mode
   else if (action == "30") EnterListeningMode(mgr);

   // Command Line Module Stuff
   else if (action == "99") isRunning = false;

   else    std::cout << " Invalid option!\n";
}

int main () {

   AMM::DDSManager<void>* mgr = new AMM::DDSManager<void>("Config/Config.xml");
   // std::cout << "Module name: " + mgr->m_moduleName << std::endl;
   // std::cout << "Part ID: " << mgr->m_participant->getAttributes().rtps.participantID << std::endl;
   // std::cout << "Dom ID: " << mgr->m_participant->getAttributes().rtps.builtin.domainId <<std::endl;

   std::string errmsg;

   if (mgr->InitializeAssessment(errmsg) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->InitializeEventFragment(errmsg) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->InitializeEventRecord(errmsg) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->InitializeFragmentAmendmentRequest(errmsg) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->InitializeLog(errmsg) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->InitializeModuleConfiguration(errmsg) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->InitializeOmittedEvent(errmsg) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->InitializeOperationalDescription(errmsg) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->InitializePhysiologyModification(errmsg) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->InitializePhysiologyValue(errmsg) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->InitializePhysiologyWaveform(errmsg) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->InitializeRenderModification(errmsg) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->InitializeSimulationControl(errmsg) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->InitializeStatus(errmsg) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->InitializeTick(errmsg) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->InitializeInstrumentData(errmsg) != 0) {
      std::cout << errmsg << std::endl;
   }

   if (mgr->InitializeCommand(errmsg) != 0) {
      std::cout << errmsg << std::endl;
   }

   // std::cout << mgr->m_assessment->m_type->getName() << std::endl;

   for (;;) {
      Menu(mgr);
      std::this_thread::sleep_for(std::chrono::milliseconds(200));

      if (!isRunning) break;
   }

   mgr->Shutdown();
   std::this_thread::sleep_for(std::chrono::milliseconds(100));
   delete mgr;

   return 0;
}
