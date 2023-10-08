package com.example.myapplication

import android.annotation.SuppressLint
import android.graphics.BitmapFactory
import android.util.Log
import android.widget.ImageView
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken
import org.eclipse.paho.client.mqttv3.MqttCallback
import org.eclipse.paho.client.mqttv3.MqttClient
import org.eclipse.paho.client.mqttv3.MqttConnectOptions
import org.eclipse.paho.client.mqttv3.MqttException
import org.eclipse.paho.client.mqttv3.MqttMessage
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence


@Suppress("unused")
class ConnectMQTT(private var brokerURL: String, private var clientID: String, private var topic: String) : AppCompatActivity() {

    companion object {
        const val TAG = "AndroidMqttClient"
    }

    @SuppressLint("SetTextI18n")
    fun connectMQTT(): MqttClient {
        val persistence = MemoryPersistence()
        val options = MqttConnectOptions()
        val client = MqttClient(this.brokerURL, this.clientID, persistence)
        options.isAutomaticReconnect = true
        options.isCleanSession = true
        try {
            client.connect()
            Log.d(TAG, "Connected to: ${this.topic}")
        } catch (ex: MqttException) {
            Log.e(TAG, "Exception when try to connect to: ${this.topic} : $ex ")
        }
        return client
    }

    fun publishMQTT(client: MqttClient, message: String) {
        val mqttMessage = MqttMessage(message.toByteArray())
        try {
            client.publish(this.topic, mqttMessage)
            Log.d(TAG, "Published message $message on topic: ${this.topic}")
        } catch (ex: MqttException) {
            Log.e(TAG, "Exception when publish on topic: ${this.topic} : $ex")
        }
    }

    fun subscribeTextMQTT(client: MqttClient, topic: String, view: TextView) {
        try {
            Log.d(TAG, "Connected to MQTT channel: $topic")
            Log.d(TAG, "Client is connected: " + client.isConnected)
            if (client.isConnected) {
                client.subscribe(topic, 0)
                client.setCallback(object : MqttCallback {
                    @SuppressLint("SetTextI18n")
                    override fun connectionLost(cause: Throwable) {
                        Log.e(TAG, "Connection to MQTT lost on: $topic : $cause")
                        view.text = "Connection Lost"
                    }
                    @Throws(Exception::class)
                    override fun messageArrived(topic: String, message: MqttMessage) {
                        val receivedTextMQTT = String(message.payload)
                        view.text = receivedTextMQTT
                        Log.d(TAG, "Received message: $receivedTextMQTT on topic + $topic)")
                    }

                    override fun deliveryComplete(token: IMqttDeliveryToken) {}
                })
            }
        } catch (ex: MqttException) {
            Log.e(TAG, "Exception when try to subscribe  to MQTT topic: $topic : $ex")
        }
    }


    fun subscribeImageMQTT(client: MqttClient, topic: String, view: ImageView) {
        try {
            Log.d(TAG, "Connected to MQTT channel: $topic")
            Log.d(TAG, "Client is connected: " + client.isConnected)
            if (client.isConnected) {
                client.subscribe(topic, 0)
                client.setCallback(object : MqttCallback {
                    @SuppressLint("SetTextI18n")
                    override fun connectionLost(cause: Throwable) {
                        Log.e(TAG, "Connection to MQTT lost on: $topic : $cause")
                    }
                    @Throws(Exception::class)
                    override fun messageArrived(topic: String, message: MqttMessage) {
                        val receivedByteArrayMQTT = message.payload
                        val receivedBitmapMQTT = BitmapFactory.decodeByteArray(receivedByteArrayMQTT,0, receivedByteArrayMQTT.size)
                        runOnUiThread {
                            view.setImageBitmap(receivedBitmapMQTT)
                        }
                        Log.d(TAG, "Received photo on topic + $topic)")
                    }

                    override fun deliveryComplete(token: IMqttDeliveryToken) {}
                })
            }
        } catch (ex: MqttException) {
            Log.e(TAG, "Exception when try to subscribe to MQTT topic: $topic : $ex")
        }
    }

    fun unsubscribeMQTT(topic:String, client: MqttClient) {
        try {
            client.unsubscribe(topic)
            Log.w(TAG, "Unsubscribed MQTT topic $topic")
        } catch (ex: MqttException) {
            Log.e(TAG, "Exception when try to unsubscribe MQTT topic $topic : $ex")

        }
    }

    fun disconnectMQTT(client: MqttClient) {
        if (client.isConnected) {
            client.disconnect()
        } else {
            Log.e(TAG, "Exception when disconnect with: ${this.brokerURL}")
        }
    }
}




