#ifndef PROCESS_H
#define PROCESS_H


class process
{
    public:
        process(int id, int creationDate, int durationTime, int priority);
        virtual ~process();
        int GetID() { return ID; }
        void SetID(int val) { ID = val; }
        int GetcreationDate() { return creationDate; }
        void SetcreationDate(int val) { creationDate = val; }
        int GetdurationTime() { return durationTime; }
        void SetdurationTime(int val) { durationTime = val; }
        int GetexecutionTime() { return executionTime; }
        void SetexecutionTime(int val) { executionTime = val; }
        int Getpriority() { return priority; }
        void Setpriority(int val) { priority = val; }
        int Getstate() { return state; }
        void Setstate(int val) { state = val; }
        int GetstartDate() { return startDate; }
        void SetstartDate(int val) { startDate = val; }
        int GetendDate() { return endDate; }
        void SetendDate(int val) { endDate = val; }

    protected:
    private:
        int ID;
        int creationDate;
        int durationTime;
        int executionTime;
        int priority;
        int state; // 0-nova, 1-pronta, 2-rodando, 3-terminada
        int startDate;
        int endDate;


};

#endif // PROCESS_H
