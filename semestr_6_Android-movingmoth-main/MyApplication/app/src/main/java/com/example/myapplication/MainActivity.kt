@file:Suppress("ASSIGNED_BUT_NEVER_ACCESSED_VARIABLE")

package com.example.myapplication

import android.annotation.SuppressLint
import android.graphics.Color
import android.os.Bundle
import android.view.Menu
import android.view.MenuItem
import androidx.appcompat.app.AppCompatActivity
import android.widget.ImageButton
import android.view.MotionEvent
import android.widget.Button
import android.widget.TextView
import androidx.appcompat.widget.Toolbar
import com.example.myapplication.databinding.PilotLayoutBinding
import com.example.myapplication.databinding.CameraLayoutBinding
import com.example.myapplication.databinding.SensorsLayoutBinding
import org.eclipse.paho.client.mqttv3.*
import android.widget.ImageView


open class MainActivity : AppCompatActivity() {
    private lateinit var binding: PilotLayoutBinding
    private lateinit var bindingCamera: CameraLayoutBinding
    private lateinit var bindingSensors: SensorsLayoutBinding

    private val instanceMQTT =
        ConnectMQTT("tcp://192.168.27.226:8883", "Android_client", "mqtt/steering")
    private var client = instanceMQTT.connectMQTT()

    fun colorPilotMainText(Text: String) {
        val title = findViewById<TextView>(R.id.TitleView)
        val r: Int = (0..255).random()
        val g: Int = (0..255).random()
        val b: Int = (0..255).random()
        title.text = Text
        title.setTextColor(Color.rgb(r, g, b))
    }

    fun unsubscribeMQTTAll() {
        instanceMQTT.unsubscribeMQTT("mqtt/distance", client)
        instanceMQTT.unsubscribeMQTT("mqtt/liftlevel", client)
        instanceMQTT.unsubscribeMQTT("mqtt/speed", client)
        instanceMQTT.unsubscribeMQTT("mqtt/camera", client)

    }


    @SuppressLint("ClickableViewAccessibility", "SetJavaScriptEnabled")
    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        return when (item.itemId) {
            R.id.Pilot -> {
                setContentView(binding.root)
                val toolbar = findViewById<Toolbar>(R.id.toolbar)
                setSupportActionBar(toolbar)
                true
            }

            R.id.camera -> {

                setContentView(bindingCamera.root)
                val toolbar = findViewById<Toolbar>(R.id.toolbar)
                val cameraButton = findViewById<Button>(R.id.cameraButton)
                val cameraImageView = findViewById<ImageView>(R.id.cameraImageView)
                setSupportActionBar(toolbar)
                cameraButton.setOnClickListener {
                    unsubscribeMQTTAll()
                    instanceMQTT.subscribeImageMQTT(client, "mqtt/camera", cameraImageView)
                }
                true
            }

            R.id.sensors -> {
                setContentView(bindingSensors.root)
                val toolbar = findViewById<Toolbar>(R.id.toolbar)
                setSupportActionBar(toolbar)
                val subDistance = findViewById<Button>(R.id.DistanceSensorsSub)
                val subLiftLevel = findViewById<TextView>(R.id.LiftLevelSub)
                val subSpeedOfPlatform = findViewById<TextView>(R.id.SpeedOfPlatformSub)
                val textDistance = findViewById<TextView>(R.id.DistanceSensorsText)
                val textLiftLevel = findViewById<TextView>(R.id.LiftLevelText)
                val textSpeedOfPlatform = findViewById<TextView>(R.id.SpeedOfPlatformText)

                subDistance.setOnClickListener {
                    this.unsubscribeMQTTAll()
                    instanceMQTT.subscribeTextMQTT(client, "mqtt/distance", textDistance)

                }

                subLiftLevel.setOnClickListener {
                    this.unsubscribeMQTTAll()
                    instanceMQTT.subscribeTextMQTT(client, "mqtt/liftlevel", textLiftLevel)

                }

                subSpeedOfPlatform.setOnClickListener {
                    this.unsubscribeMQTTAll()
                    instanceMQTT.subscribeTextMQTT(client, "mqtt/speed", textSpeedOfPlatform)

                }

                true
            }

            else -> super.onOptionsItemSelected(item)
        }
    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        menuInflater.inflate(R.menu.app_menu, menu)
        return true
    }

    @SuppressLint("ClickableViewAccessibility")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = PilotLayoutBinding.inflate(layoutInflater)
        bindingCamera = CameraLayoutBinding.inflate(layoutInflater)
        bindingSensors = SensorsLayoutBinding.inflate(layoutInflater)
        setContentView(binding.root)
        val toolbar = findViewById<Toolbar>(R.id.toolbar)
        setSupportActionBar(toolbar)
        val leftButton = findViewById<ImageButton>(R.id.LeftButton)
        val rightButton = findViewById<ImageButton>(R.id.RightButton)
        val upButton = findViewById<ImageButton>(R.id.UpButton)
        val backButton = findViewById<ImageButton>(R.id.BackButton)
        val liftButton = findViewById<ImageButton>(R.id.lift)
        val lowerButton = findViewById<ImageButton>(R.id.lower)
        val stopButton = findViewById<ImageButton>(R.id.StopButton)
        val mappingButton = findViewById<ImageButton>(R.id.start_mapping)
        val stopMappingButton = findViewById<ImageButton>(R.id.stop_mapping)
        var isButtonHeld = false

        fun startMovingPlatform(message: String) {
            instanceMQTT.publishMQTT(client, message)
            colorPilotMainText(message)
        }

        fun stopMovingPlatform() {
            instanceMQTT.publishMQTT(client, "Stop")
            colorPilotMainText("Stop platform")

        }

        stopButton.setOnClickListener {
            stopMovingPlatform()
            colorPilotMainText("Stop platform")
        }
        mappingButton.setOnClickListener {
            instanceMQTT.publishMQTT(client, "MAP")

        }
        stopMappingButton.setOnClickListener {
            instanceMQTT.publishMQTT(client, "STOP MAP")
        }
        liftButton.setOnTouchListener { _, event ->
            when (event.action) {
                MotionEvent.ACTION_DOWN -> {
                    isButtonHeld = true
                    startMovingPlatform("Lift")
                }

                MotionEvent.ACTION_UP, MotionEvent.ACTION_CANCEL -> {
                    isButtonHeld = false
                    stopMovingPlatform()
                }
            }
            true
        }
        lowerButton.setOnTouchListener { _, event ->
            when (event.action) {
                MotionEvent.ACTION_DOWN -> {
                    isButtonHeld = true
                    startMovingPlatform("Lower")
                }

                MotionEvent.ACTION_UP, MotionEvent.ACTION_CANCEL -> {
                    isButtonHeld = false
                    stopMovingPlatform()
                }
            }
            true
        }
        rightButton.setOnTouchListener { _, event ->
            when (event.action) {
                MotionEvent.ACTION_DOWN -> {
                    isButtonHeld = true
                    startMovingPlatform("Right")
                }

                MotionEvent.ACTION_UP, MotionEvent.ACTION_CANCEL -> {
                    isButtonHeld = false
                    stopMovingPlatform()
                }
            }
            true
        }

        leftButton.setOnTouchListener { _, event ->
            when (event.action) {
                MotionEvent.ACTION_DOWN -> {
                    isButtonHeld = true
                    startMovingPlatform("Left")
                }

                MotionEvent.ACTION_UP, MotionEvent.ACTION_CANCEL -> {
                    isButtonHeld = false
                    stopMovingPlatform()
                }
            }
            true
        }

        upButton.setOnTouchListener { _, event ->
            when (event.action) {
                MotionEvent.ACTION_DOWN -> {
                    isButtonHeld = true
                    startMovingPlatform("Forward")
                }

                MotionEvent.ACTION_UP, MotionEvent.ACTION_CANCEL -> {
                    isButtonHeld = false
                    stopMovingPlatform()
                }
            }
            true
        }
        backButton.setOnTouchListener { _, event ->
            when (event.action) {
                MotionEvent.ACTION_DOWN -> {
                    isButtonHeld = true
                    startMovingPlatform("Back")
                }

                MotionEvent.ACTION_UP, MotionEvent.ACTION_CANCEL -> {
                    isButtonHeld = false
                    stopMovingPlatform()
                }
            }
            true
        }
    }

    override fun onResume() {
        super.onResume()
        client = instanceMQTT.connectMQTT()
    }

    override fun onDestroy() {
        super.onDestroy()
        this.unsubscribeMQTTAll()
        instanceMQTT.disconnectMQTT(client)

    }


}

