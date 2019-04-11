

void setup() {
  Serial.begin(115200);
  if(!SD.begin()){
    Serial.println("Card Mount Failed");
  return;
}

void loop() {
  // put your main code here, to run repeatedly:

}
