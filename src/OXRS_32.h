/*
 * OXRS_32.h
 */

#ifndef OXRS_32_H
#define OXRS_32_H

#include <OXRS_MQTT.h>                // For MQTT pub/sub
#include <OXRS_API.h>                 // For REST API

// I2C
#define       I2C_SDA                   21
#define       I2C_SCL                   22

// REST API
#define       REST_API_PORT             80

class OXRS_32 : public Print
{
  public:
    void begin(jsonCallback config, jsonCallback command);
    void loop(void);

    // Firmware can define the config/commands it supports - for device discovery and adoption
    void setConfigSchema(JsonVariant json);
    void setCommandSchema(JsonVariant json);

    // Return a pointer to the MQTT library
    OXRS_MQTT * getMQTT(void);

    // Return a pointer to the API library
    OXRS_API * getAPI(void);

    // Helpers for publishing to stat/ and tele/ topics
    boolean publishStatus(JsonVariant json);
    boolean publishTelemetry(JsonVariant json);

    // Implement Print.h wrapper
    virtual size_t write(uint8_t);
    using Print::write;

  private:
    void _initialiseNetwork(byte * mac);
    void _initialiseMqtt(byte * mac);
    void _initialiseRestApi(void);

    boolean _isNetworkConnected(void);
};

#endif
