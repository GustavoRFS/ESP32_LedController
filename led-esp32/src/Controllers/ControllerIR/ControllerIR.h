class ControllerIR{
  public:
    static void setup();
    static bool available();
    static void readAndPerformCommand();
  private:
    static void read();
};