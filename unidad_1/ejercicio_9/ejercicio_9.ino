void task1(){
    enum class Task1States{
        INIT,
        WAIT_FOR_TIMEOUT
    };

    static Task1States task1State = Task1States::INIT;
    static uint32_t lastTime;
    static constexpr uint32_t INTERVAL = 1000;

    switch(task1State){
        case Task1States::INIT:{
            Serial.begin(115200);
            lastTime = millis();
            task1State = Task1States::WAIT_FOR_TIMEOUT;
            break;
        }

        case Task1States::WAIT_FOR_TIMEOUT:{
          uint32_t currentTime = millis();
            // evento 1:            uint32_t currentTime = millis();
            if( (currentTime - lastTime) >= INTERVAL ){
                lastTime = currentTime;
                Serial.print("mensaje a 1Hz\n");
            }
            break;
        }

        default:{
            break;
        }
    }

}



void task2(){
   enum class Task2States{
        INIT,
        WAIT_FOR_TIMEOUT
    };

    static Task2States task2State = Task2States::INIT;
    static uint32_t lastTime;
    static constexpr uint32_t INTERVAL = 1000;

    switch(task2State){
        case Task2States::INIT:{
            Serial.begin(115200);
            lastTime = millis();
            task2State = Task2States::WAIT_FOR_TIMEOUT;
            break;
        }

        case Task2States::WAIT_FOR_TIMEOUT:{
          uint32_t currentTime = millis();
            // evento 1:            uint32_t currentTime = millis();
            if( (currentTime - lastTime) >= INTERVAL ){
                lastTime = currentTime;
                Serial.print("mensaje a 0.5Hz\n");
            }
            break;
        }

        default:{
            break;
        }
    }

}

void task3(){
 enum class Task3States{
        INIT,
        WAIT_FOR_TIMEOUT
    };

    static Task3States task3State = Task3States::INIT;
    static uint32_t lastTime;
    static constexpr uint32_t INTERVAL = 1000;

    switch(task3State){
        case Task3States::INIT:{
            Serial.begin(115200);
            lastTime = millis();
            task3State = Task3States::WAIT_FOR_TIMEOUT;
            break;
        }

        case Task3States::WAIT_FOR_TIMEOUT:{
          uint32_t currentTime = millis();
            // evento 1:            uint32_t currentTime = millis();
            if( (currentTime - lastTime) >= INTERVAL ){
                lastTime = currentTime;
                Serial.print("mensaje a 0.25Hz\n");
            }
            break;
        }

        default:{
            break;
        }
    }

}

void setup()
{
    task1();
    task2();
    task3();
}

void loop()
{
    task1();
    task2();
    task3();
}