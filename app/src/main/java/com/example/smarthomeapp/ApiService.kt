package com.example.smarthomeapp

import com.google.gson.annotations.SerializedName
import retrofit2.Response
import retrofit2.http.Body
import retrofit2.http.GET
import retrofit2.http.Header
import retrofit2.http.POST

data class SetStateRequest(
    @SerializedName("state") val state: String
)

data class GenericResponse(
    @SerializedName("action_result") val actionResult: String,
    @SerializedName("current_status") val currentStatus: String
)

data class LightStatusResponse(
    @SerializedName("status_message") val statusMessage: String,
    @SerializedName("is_on") val isOn: Boolean
)

data class SetColorRequest(
    @SerializedName("color") val color: String
)

data class SetColorResponse(
    @SerializedName("message") val message: String,
    @SerializedName("new_color") val newColor: String
)

data class ConditionerStatusResponse(
    @SerializedName("status message") val statusMessage: String,
    @SerializedName("is_on") val isOn: Boolean,
    @SerializedName("current_temperature") val currentTemperature: Int
)

data class SetTempRequest(
    @SerializedName("temp") val temp: Int
)

data class DoorStatusResponse(
    @SerializedName("status_message") val statusMessage: String,
    @SerializedName("is_open") val isOpen: Boolean,
    @SerializedName("is_locked") val isLocked: Boolean
)

data class SetLockRequest(
    @SerializedName("lock") val lock: Boolean
)

interface ApiService {

    @GET("light/status")
    suspend fun getLightStatus(
        @Header("X-API-Key") apiKey: String
    ): Response<LightStatusResponse>

    @POST("light/set")
    suspend fun setLightState(
        @Header("X-API-Key") apiKey: String,
        @Body request: SetStateRequest
    ): Response<GenericResponse>

    @POST("light/set_color")
    suspend fun setLightColor(
        @Header("X-API-Key") apiKey: String,
        @Body request: SetColorRequest
    ): Response<SetColorResponse>

    @GET("door/status")
    suspend fun getDoorStatus(
        @Header("X-API-Key") apiKey: String
    ): Response<DoorStatusResponse>

    @POST("door/set_state")
    suspend fun setDoorState(
        @Header("X-API-Key") apiKey: String,
        @Body request: SetStateRequest
    ): Response<GenericResponse>

    @POST("door/set_lock")
    suspend fun setDoorLock(
        @Header("X-API-Key") apiKey: String,
        @Body request: SetLockRequest
    ): Response<GenericResponse>

    @GET("conditioner/status")
    suspend fun getConditionerStatus(
        @Header("X-API-Key") apiKey: String
    ): Response<ConditionerStatusResponse>

    @POST("conditioner/set")
    suspend fun setConditionerState(
        @Header("X-API-Key") apiKey: String,
        @Body request: SetStateRequest
    ): Response<GenericResponse>

    @POST("conditioner/set_temp")
    suspend fun setConditionerTemp(
        @Header("X-API-Key") apiKey: String,
        @Body request: SetTempRequest
    ): Response<GenericResponse>
}