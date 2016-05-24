

class ProcessControl{
public:
	void setSimulationMode(bool simulationMode)           { _simulationMode = simulationMode;         }
	
	void run();
private:

    bool _simulationMode;	
};