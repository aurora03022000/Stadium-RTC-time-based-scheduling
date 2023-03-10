 #include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>

const char *ssid = "ESP8266 AP";
const char *password = "password";

ESP8266WebServer server(80);

void handleRoot() {
  if (server.hasArg("submit")) {
    timeValue = server.arg("time");
    
    if(timeValue == ""){
      timeValue = "0:0";
    }

    Serial1.println(timeValue);
    
    server.send(200, "text/html", "<!DOCTYPE html><html lang='en'>"
    "<head>"
    "<meta charset='UTF-8'>"
    "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
    "<title>Manual Settings</title>"
    "</head>"
    "<style>"
      "label{"
        "width: 200px;"
      "}"
      ".input{"
        "width: 100%;"
        "cursor: pointer;"
      "}"
      ".input1{"
        "width: 100%;"
        "cursor: pointer;"
      "}"
      ".inputNumber{"
        "width: 100%;"
        "cursor: pointer;"
      "}"
      "input:disabled {"
        "background-color: lightgray;"
        "color: black;"
        "border: 2px solid gray;"
        "cursor: not-allowed;"
      "}"
      ".submit:disabled:hover {"
        "background-color: lightgray;"
        "color: black;"
      "}"
      ".submit{"
        "width: 100%; "
        "margin-top: 20px; "
        "cursor: pointer; "
        "padding: 14px 20px; "
        "font-size: 15px;"
        "background-color: #1C942A; "
        "color: white; "
        "border: 1px solid black; "
        "border-radius: 2px;"
        "}"
      ".submit:hover"
        "background-color: #187C24;"
      "}"
      "</style>"
      "<body style='font-family: Arial, Helvetica, sans-serif; '>"
        "<div style='margin: 0 auto; text-align: center;'>"
          "<p style='font-size: 15px; color: green; margin-bottom: 20px; margin-top: 40px' id='updated'>Time has been updated successfully</p>"
          "<h1 style='font-size: 35px; font-family: arial; margin-top: 50px;'>Manual settings</h1>"
          "<p style='font-size:13px; text-align: center;'>Update the time here if it is not accuracte and as well as the open and closing time.</p>"
          "<div style='margin-top: 50px;display: inline-block; margin: auto 0; text-align: left; margin-bottom: 40px;'>"
          "<form method='post' id='form'>"
            "<div style='display: flex; margin-bottom: 5px; margin-top: 20px;'>"
              "<label style='margin: auto 0;' >Time</label>"
              "<input class='input1' name='time' id='time' type='time' style='padding: 13px 20px; border: 1px solid black; border-radius: 2px; margin-right: 20px;' />"
            "</div>"
            "<div style='display: flex;margin-bottom: 5px;'>"
              "<label style='margin: auto 0;'>Time open</label>"
              "<input disabled name='timeOpen' id='timeOpen' class='input' type='time' style='cursor: pointer; padding: 13px 20px; border: 1px solid black; border-radius: 2px;' /><br/>"
              "<input type='checkbox'id='timeOpenCheckbox'  style='cursor: pointer;padding: 10px 10px; border: 1px solid black; border-radius: 2px; width: 7%;'/>"
            "</div>"
            "<div style='display: flex;margin-bottom: 5px;'>"
              "<label style='margin: auto 0;'>Time Close</label>"
              "<input disabled name='timeClose' id='timeClose' class='input' type='time' style='cursor: pointer; padding: 13px 20px; border: 1px solid black; border-radius: 2px;' /><br/>"
              "<input type='checkbox' id='timeCloseCheckbox' style=' cursor: pointer;padding: 10px 10px; border: 1px solid black; border-radius: 2px; width: 7%;'/>"
            "</div>"
            "<input type='submit' name='submit' id='submit' class='submit' value='Update time' />"
          "</form>"
        "</div>"
      "</div>"
    "</body>"
    "<script>"
      "const checkbox = document.getElementById('timeCheckbox');const checkbox4 = document.getElementById('timeOpenCheckbox');const checkbox5 = document.getElementById('timeCloseCheckbox');"
      "const input = document.getElementById('time');const input4 = document.getElementById('timeOpen');const input5 = document.getElementById('timeClose');"
      "const submitButton = document.getElementById('submit');"
      "input.oninput = function() {"
        "var countDisable = 0;"
        "if (input.value.length > 0) {"
          "if(input4.value.length <= 0 && checkbox4.checked){"
            "countDisable = 1;"
          "}"
          "else if(input5.value.length <= 0 && checkbox5.checked){"
            "countDisable = 1;"
          "}"
          "if(countDisable > 0){"
            "submitButton.disabled = true;"
          "}"
          "else if(countDisable == 0){"
            "submitButton.disabled = false;"
          "}"
        "}"
        "else {"
          "submitButton.disabled = true;"
        "}"
      "};"
  "input4.oninput = function() {"
    "var countDisable = 0;"
    "if (input4.value.length > 0 && checkbox4.checked && input.value.length > 0) {"
      "if(input5.value.length <= 0 && checkbox5.checked){"
        "countDisable = 1;"
      "}"
      "if(countDisable > 0){"
        "submitButton.disabled = true;"
      "}"
      "else if(countDisable == 0){"
        "submitButton.disabled = false;"
      "}"
    "}"
    "else {"
      "submitButton.disabled = true;"
    "}"
  "};"
  "input5.oninput = function() {"
    "var countDisable = 0;"
    "if (input5.value.length > 0 && checkbox5.checked && input.value.length > 0) {"
      "if(input4.value.length <= 0 && checkbox4.checked){"
        "countDisable = 1;"
      "}"
      "if(countDisable > 0){"
        "submitButton.disabled = true;"
      "}"
      "else if(countDisable == 0){"
        "submitButton.disabled = false;"
      "}"
    "}"
    "else {"
      "submitButton.disabled = true;"
    "}"
  "};"
  "checkbox4.addEventListener('change', function () {"
    "if (checkbox4.checked) {"
      "input4.disabled = false;"
      "if(input.value.length > 0 && input4.value.length > 0 && input5.value.length > 0){"
        "submitButton.disabled = false;"
      "}"
      "else{"
        "submitButton.disabled = true;"
      "}"
    "}"
    "else {"   
      "if(input.value.length > 0){"
        "submitButton.disabled = false;"
      "}"
      "else{"
        "submitButton.disabled = true;"
      "}"
      "input4.value = '';"
      "input4.disabled = true;"
    "}"
  "});" 
  "checkbox5.addEventListener('change', function () {"
    "if (checkbox5.checked) {"
      "input5.disabled = false;"
      "if(input.value.length > 0 && input4.value.length > 0 && input5.value.length > 0){"
        "submitButton.disabled = false;"
      "}"
      "else{"
        "submitButton.disabled = true;"
      "}"
    "}"
    "else {"   
      "if(input.value.length > 0){"
        "submitButton.disabled = false;"
      "}"
      "else{"
        "submitButton.disabled = true;"
      "}"
      "input5.value = '';"
      "input5.disabled = true;"
    "}"
  "});"
  "var date = new Date();"
      "const now = new Date();"
      "document.getElementById('time').value = (date.getHours()<10?'0':'') + date.getHours()  + ':' + (date.getMinutes()<10?'0':'') + date.getMinutes();"
      "const element = document.getElementById('updated');"
      "element.style.display = 'block';"
      "setTimeout(function() {"
      "element.style.display = 'none';"
      "}, 2000);"
     "window.onload = function() {"
        "if (input.value === '') {"
          "submitButton.disabled = true;"
        "}"
      "}"
  "</script>"
  "</html>"          
    );
  } 
  
  else {
    server.send(200, "text/html", "<!DOCTYPE html><html lang='en'>"
    "<head>"
    "<meta charset='UTF-8'>"
    "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
    "<title>Manual Settings</title>"
    "</head>"
    "<style>"
      "label{"
        "width: 200px;"
      "}"
      ".input{"
        "width: 100%;"
        "cursor: pointer;"
      "}"
      ".input1{"
        "width: 100%;"
        "cursor: pointer;"
      "}"
      ".inputNumber{"
        "width: 100%;"
        "cursor: pointer;"
      "}"
      "input:disabled {"
        "background-color: lightgray;"
        "color: black;"
        "border: 2px solid gray;"
        "cursor: not-allowed;"
      "}"
      ".submit:disabled:hover {"
        "background-color: lightgray;"
        "color: black;"
      "}"
      ".submit{"
        "width: 100%; "
        "margin-top: 20px; "
        "cursor: pointer; "
        "padding: 14px 20px; "
        "font-size: 15px;"
        "background-color: #1C942A; "
        "color: white; "
        "border: 1px solid black; "
        "border-radius: 2px;"
        "}"
      ".submit:hover"
        "background-color: #187C24;"
      "}"
      "</style>"
      "<body style='font-family: Arial, Helvetica, sans-serif; '>"
        "<div style='margin: 0 auto; text-align: center;'>"
          "<h1 style='font-size: 35px; font-family: arial; margin-top: 50px;'>Manual settings</h1>"
          "<p style='font-size:13px; text-align: center;'>Update the time here if it is not accuracte and as well as the open and closing time.</p>"
          "<div style='margin-top: 50px;display: inline-block; margin: auto 0; text-align: left; margin-bottom: 40px;'>"
          "<form method='post' id='form'>"
            "<div style='display: flex; margin-bottom: 5px; margin-top: 20px;'>"
              "<label style='margin: auto 0;' >Time</label>"
              "<input class='input1' name='time' id='time' type='time' style='padding: 13px 20px; border: 1px solid black; border-radius: 2px; margin-right: 20px;' />"
            "</div>"
            "<div style='display: flex;margin-bottom: 5px;'>"
              "<label style='margin: auto 0;'>Time open</label>"
              "<input disabled name='timeOpen' id='timeOpen' class='input' type='time' style='cursor: pointer; padding: 13px 20px; border: 1px solid black; border-radius: 2px;' /><br/>"
              "<input type='checkbox'id='timeOpenCheckbox'  style='cursor: pointer;padding: 10px 10px; border: 1px solid black; border-radius: 2px; width: 7%;'/>"
            "</div>"
            "<div style='display: flex;margin-bottom: 5px;'>"
              "<label style='margin: auto 0;'>Time Close</label>"
              "<input disabled name='timeClose' id='timeClose' class='input' type='time' style='cursor: pointer; padding: 13px 20px; border: 1px solid black; border-radius: 2px;' /><br/>"
              "<input type='checkbox' id='timeCloseCheckbox' style=' cursor: pointer;padding: 10px 10px; border: 1px solid black; border-radius: 2px; width: 7%;'/>"
            "</div>"
            "<input type='submit' name='submit' id='submit' class='submit' value='Update time' />"
          "</form>"
        "</div>"
      "</div>"
    "</body>"
    "<script>"
      "const checkbox = document.getElementById('timeCheckbox');const checkbox4 = document.getElementById('timeOpenCheckbox');const checkbox5 = document.getElementById('timeCloseCheckbox');"
      "const input = document.getElementById('time');const input4 = document.getElementById('timeOpen');const input5 = document.getElementById('timeClose');"
      "const submitButton = document.getElementById('submit');"
      "input.oninput = function() {"
        "var countDisable = 0;"
        "if (input.value.length > 0) {"
          "if(input4.value.length <= 0 && checkbox4.checked){"
            "countDisable = 1;"
          "}"
          "else if(input5.value.length <= 0 && checkbox5.checked){"
            "countDisable = 1;"
          "}"
          "if(countDisable > 0){"
            "submitButton.disabled = true;"
          "}"
          "else if(countDisable == 0){"
            "submitButton.disabled = false;"
          "}"
        "}"
        "else {"
          "submitButton.disabled = true;"
        "}"
      "};"
  "input4.oninput = function() {"
    "var countDisable = 0;"
    "if (input4.value.length > 0 && checkbox4.checked && input.value.length > 0) {"
      "if(input5.value.length <= 0 && checkbox5.checked){"
        "countDisable = 1;"
      "}"
      "if(countDisable > 0){"
        "submitButton.disabled = true;"
      "}"
      "else if(countDisable == 0){"
        "submitButton.disabled = false;"
      "}"
    "}"
    "else {"
      "submitButton.disabled = true;"
    "}"
  "};"
  "input5.oninput = function() {"
    "var countDisable = 0;"
    "if (input5.value.length > 0 && checkbox5.checked && input.value.length > 0) {"
      "if(input4.value.length <= 0 && checkbox4.checked){"
        "countDisable = 1;"
      "}"
      "if(countDisable > 0){"
        "submitButton.disabled = true;"
      "}"
      "else if(countDisable == 0){"
        "submitButton.disabled = false;"
      "}"
    "}"
    "else {"
      "submitButton.disabled = true;"
    "}"
  "};"
  "checkbox4.addEventListener('change', function () {"
    "if (checkbox4.checked) {"
      "input4.disabled = false;"
      "if(input.value.length > 0 && input4.value.length > 0 && input5.value.length > 0){"
        "submitButton.disabled = false;"
      "}"
      "else{"
        "submitButton.disabled = true;"
      "}"
    "}"
    "else {"   
      "if(input.value.length > 0){"
        "submitButton.disabled = false;"
      "}"
      "else{"
        "submitButton.disabled = true;"
      "}"
      "input4.value = '';"
      "input4.disabled = true;"
    "}"
  "});" 
  "checkbox5.addEventListener('change', function () {"
    "if (checkbox5.checked) {"
      "input5.disabled = false;"
      "if(input.value.length > 0 && input4.value.length > 0 && input5.value.length > 0){"
        "submitButton.disabled = false;"
      "}"
      "else{"
        "submitButton.disabled = true;"
      "}"
    "}"
    "else {"   
      "if(input.value.length > 0){"
        "submitButton.disabled = false;"
      "}"
      "else{"
        "submitButton.disabled = true;"
      "}"
      "input5.value = '';"
      "input5.disabled = true;"
    "}"
  "});"
  "var date = new Date();"
      "const now = new Date();"
      "document.getElementById('time').value = (date.getHours()<10?'0':'') + date.getHours()  + ':' + (date.getMinutes()<10?'0':'') + date.getMinutes();"
  "window.onload = function() {"
        "if (input.value === '') {"
          "submitButton.disabled = true;"
        "}"
      "}"    
  "</script>"
  "</html>"          
    );
  }
  
 
}

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  Serial.println("WiFi AP started");

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/", handleRoot);
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}
