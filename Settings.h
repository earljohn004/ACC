#ifndef Settings_h
#define Settings_h

class Settings{
    private:
        int transition_duration_;
        char* cafe_name_;
       
    public:
        Settings();
        int getTransitionSetting();
        char * getCafeNameSetting();
    private:
        int setTransitionSetting(int transition);
        char * setCafeNameSetting();

};

#endif
