package com.example.smarthomeapp

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import android.widget.Toast
import androidx.lifecycle.lifecycleScope
import kotlinx.coroutines.launch
import java.io.IOException

class MainActivity : AppCompatActivity() {

    private val API_KEY = "my-secret-key-12345"

    private lateinit var tvLightStatus: TextView
    private lateinit var btnLightOn: Button
    private lateinit var btnLightOff: Button
    private lateinit var etColor: EditText
    private lateinit var btnSetColor: Button

    private lateinit var tvDoorStatus: TextView
    private lateinit var btnDoorOpen: Button
    private lateinit var btnDoorClose: Button
    private lateinit var btnDoorLock: Button
    private lateinit var btnDoorUnlock: Button

    private lateinit var tvConditionerStatus: TextView
    private lateinit var btnCondOn: Button
    private lateinit var btnCondOff: Button
    private lateinit var etTemperature: EditText
    private lateinit var btnSetTemp: Button

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        tvLightStatus = findViewById(R.id.tvLightStatus)
        btnLightOn = findViewById(R.id.btnLightOn)
        btnLightOff = findViewById(R.id.btnLightOff)
        etColor = findViewById(R.id.etColor)
        btnSetColor = findViewById(R.id.btnSetColor)

        tvDoorStatus = findViewById(R.id.tvDoorStatus)
        btnDoorOpen = findViewById(R.id.btnDoorOpen)
        btnDoorClose = findViewById(R.id.btnDoorClose)
        btnDoorLock = findViewById(R.id.btnDoorLock)
        btnDoorUnlock = findViewById(R.id.btnDoorUnlock)

        tvConditionerStatus = findViewById(R.id.tvConditionerStatus)
        btnCondOn = findViewById(R.id.btnCondOn)
        btnCondOff = findViewById(R.id.btnCondOff)
        etTemperature = findViewById(R.id.etTemperature)
        btnSetTemp = findViewById(R.id.btnSetTemp)

        setupListeners()
        refreshAllStatuses()
    }

    private fun setupListeners() {
        btnLightOn.setOnClickListener { setLightState("on") }
        btnLightOff.setOnClickListener { setLightState("off") }
        btnSetColor.setOnClickListener { setLightColor() }

        btnDoorOpen.setOnClickListener { setDoorState("open") }
        btnDoorClose.setOnClickListener { setDoorState("close") }
        btnDoorLock.setOnClickListener { setDoorLock(true) }
        btnDoorUnlock.setOnClickListener { setDoorLock(false) }

        btnCondOn.setOnClickListener { setConditionerState("on") }
        btnCondOff.setOnClickListener { setConditionerState("off") }
        btnSetTemp.setOnClickListener { setTemperature() }
    }

    private fun refreshAllStatuses() {
        getLightStatus()
        getDoorStatus()
        getConditionerStatus()
    }

    private fun getLightStatus() {
        lifecycleScope.launch {
            try {
                val response = RetrofitClient.instance.getLightStatus(API_KEY)
                if (response.isSuccessful) {
                    tvLightStatus.text = response.body()?.statusMessage ?: "Empty response"
                } else {
                    handleApiError("Light Status", response.code())
                }
            } catch (e: Exception) {
                handleNetworkError(e)
            }
        }
    }

    private fun setLightState(state: String) {
        lifecycleScope.launch {
            try {
                val response = RetrofitClient.instance.setLightState(API_KEY, SetStateRequest(state))
                if (response.isSuccessful) {
                    getLightStatus()
                } else {
                    handleApiError("Light Set", response.code())
                }
            } catch (e: Exception) {
                handleNetworkError(e)
            }
        }
    }

    private fun setLightColor() {
        val color = etColor.text.toString().lowercase().trim()
        if (color.isEmpty()) {
            Toast.makeText(this, "Please enter a color", Toast.LENGTH_SHORT).show()
            return
        }

        lifecycleScope.launch {
            try {
                val response = RetrofitClient.instance.setLightColor(API_KEY, SetColorRequest(color))
                if (response.isSuccessful) {
                    val colorResponse = response.body()
                    if (colorResponse != null) {
                        if (colorResponse.message.contains("Invalid")) {
                            Toast.makeText(this@MainActivity, colorResponse.message, Toast.LENGTH_LONG).show()
                        } else {
                            etColor.text.clear()
                        }
                    }
                    getLightStatus()
                } else {
                    handleApiError("Set Color", response.code())
                }
            } catch (e: Exception) {
                handleNetworkError(e)
            }
        }
    }

    private fun getDoorStatus() {
        lifecycleScope.launch {
            try {
                val response = RetrofitClient.instance.getDoorStatus(API_KEY)
                if (response.isSuccessful) {
                    val status = response.body()
                    if (status != null) {
                        val openStatus = if (status.isOpen) "(Open)" else "(Closed)"
                        tvDoorStatus.text = "${status.statusMessage} $openStatus"
                    }
                } else {
                    handleApiError("Door Status", response.code())
                }
            } catch (e: Exception) {
                handleNetworkError(e)
            }
        }
    }

    private fun setDoorState(state: String) {
        lifecycleScope.launch {
            try {
                val response = RetrofitClient.instance.setDoorState(API_KEY, SetStateRequest(state))
                if (response.isSuccessful) {
                    getDoorStatus()
                } else {
                    handleApiError("Door State", response.code())
                }
            } catch (e: Exception) {
                handleNetworkError(e)
            }
        }
    }

    private fun setDoorLock(lock: Boolean) {
        lifecycleScope.launch {
            try {
                val response = RetrofitClient.instance.setDoorLock(API_KEY, SetLockRequest(lock))
                if (response.isSuccessful) {
                    getDoorStatus()
                } else {
                    handleApiError("Door Lock", response.code())
                }
            } catch (e: Exception) {
                handleNetworkError(e)
            }
        }
    }

    private fun getConditionerStatus() {
        lifecycleScope.launch {
            try {
                val response = RetrofitClient.instance.getConditionerStatus(API_KEY)
                if (response.isSuccessful) {
                    val status = response.body()
                    if (status != null) {
                        val onOff = if (status.isOn) "On" else "Off"
                        tvConditionerStatus.text = "Status: $onOff, Temp: ${status.currentTemperature}°C"
                    }
                } else {
                    handleApiError("Cond Status", response.code())
                }
            } catch (e: Exception) {
                handleNetworkError(e)
            }
        }
    }

    private fun setConditionerState(state: String) {
        lifecycleScope.launch {
            try {
                val response = RetrofitClient.instance.setConditionerState(API_KEY, SetStateRequest(state))
                if (response.isSuccessful) {
                    getConditionerStatus()
                } else {
                    handleApiError("Cond State", response.code())
                }
            } catch (e: Exception) {
                handleNetworkError(e)
            }
        }
    }

    private fun setTemperature() {
        val tempString = etTemperature.text.toString()
        if (tempString.isEmpty()) {
            Toast.makeText(this, "Please enter a temperature", Toast.LENGTH_SHORT).show()
            return
        }

        val temp = tempString.toInt()

        if (temp < 13 || temp > 31) {
            Toast.makeText(this, "Temperature must be between 13 and 31", Toast.LENGTH_LONG).show()
            return
        }

        lifecycleScope.launch {
            try {
                val response = RetrofitClient.instance.setConditionerTemp(API_KEY, SetTempRequest(temp))
                if (response.isSuccessful) {
                    getConditionerStatus()
                    etTemperature.text.clear()
                } else {
                    handleApiError("Set Temp", response.code())
                }
            } catch (e: Exception) {
                handleNetworkError(e)
            }
        }
    }

    private fun handleApiError(source: String, code: Int) {
        Log.e("MainActivity", "$source API Error: $code")
        Toast.makeText(this, "$source Error: $code", Toast.LENGTH_SHORT).show()
    }

    private fun handleNetworkError(e: Exception) {
        Log.e("MainActivity", "Network Error", e)
        Toast.makeText(this, "Network Error: Check connection or server", Toast.LENGTH_SHORT).show()
    }
}