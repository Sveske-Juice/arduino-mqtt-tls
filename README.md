# arduino-mqtt-tls
This project uses [PubSubClient](https://pubsubclient.knolleary.net/) library and [WiFiClientSecure](https://github.com/hugethor/WiFiClientSecure) to allow the arduino to connect to an encrypted MQTT Broker.

# NOTE
It actually doesn't validate the Certificate, because it disables security in WiFIClientSecure:
`wifiClient.setInsecure();`
It is not intended for security! it is more a bypass to allow connections to TLS encrypted MQTT brokers, since not using WiFiClientSecure for the connection with PubSubClient will return a rc=-2 error code.
