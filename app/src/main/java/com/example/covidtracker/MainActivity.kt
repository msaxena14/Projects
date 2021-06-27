package com.example.covidtracker

import android.os.Bundle
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.android.volley.Request
import com.android.volley.toolbox.JsonObjectRequest
import com.android.volley.toolbox.Volley
import org.json.JSONException

@Suppress("NAME_SHADOWING")
class MainActivity : AppCompatActivity() {
    lateinit var worldCasesTV:TextView
    lateinit var worldRecoveredTV:TextView
    lateinit var worldDeathsTV:TextView
    lateinit var CountryCasesTV:TextView
    lateinit var CountryRecoveredTV:TextView
    lateinit var CountryDeathsTV:TextView
    lateinit var StateRV:RecyclerView
    lateinit var StateRVAdapter:StateRVAdapter
    lateinit var StateList:List<StateModal>


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        worldCasesTV = findViewById(R.id.idTVWorldCases)
        worldDeathsTV = findViewById(R.id.idTVWorldDeaths)
        worldRecoveredTV = findViewById(R.id.idTVRecovered)
        CountryCasesTV = findViewById(R.id.idTVIndiaCases)
        CountryDeathsTV = findViewById(R.id.idTVIndiaDeaths)
        CountryRecoveredTV = findViewById(R.id.idTVIndiaRecovered)
        StateRV = findViewById(R.id.idRVStates)
        StateList = ArrayList<StateModal>()
    }

    private fun getStateInfo(){
        val url = "https://api.rootnet.in/covid19-in/stats/latest"
        val queue = Volley.newRequestQueue(this@MainActivity)
        val request =
            JsonObjectRequest(Request.Method.GET, url,null,{ response->
                try {
                    val dataObj = response.getJSONObject("data")
                    val summaryObj = dataObj.getJSONObject("summary")
                    val cases:Int = summaryObj.getInt("total")
                    val recovered:Int = summaryObj.getInt("discharged")
                    val deaths:Int = summaryObj.getInt("deaths")

                    CountryCasesTV.text = cases.toString()
                    CountryRecoveredTV.text = recovered.toString()
                    CountryDeathsTV.text = deaths.toString()

                    val regionalArray = dataObj.getJSONArray("reginonal")
                    for(i in 0 until regionalArray.length()){
                        val regionalObj = regionalArray.getJSONObject(i)
                        val stateName:String = regionalObj.getString("loc")
                        val cases:Int = regionalObj.getInt("totalConfirmed")
                        val deaths:Int = regionalObj.getInt("deaths")
                        val recovered:Int = regionalObj.getInt("discharged")

                        val StateModal = StateModal(stateName,recovered,deaths,cases)
                        StateList = StateList+StateModal

                    }

                    StateRVAdapter = StateRVAdapter(StateList)
                    StateRV.layoutManager = LinearLayoutManager(this)
                    StateRV.adapter = StateRVAdapter


                }catch (e:JSONException){
                    e.printStackTrace()
                }

            },{ _ ->
                run {
                    Toast.makeText(this, "Fail to get data", Toast.LENGTH_SHORT).show()
                }
            })
            queue.add(request)
    }

    private fun getWorldInfo(){
        val url = "https://corona.lmao.ninja/v3/covidd-19/all"
        val queue = Volley.newRequestQueue(this@MainActivity)
        val request =
            JsonObjectRequest(Request.Method.GET, url, null,{ response ->
                try {
                    val worldCases: Int = response.getInt("cases")
                    val worldRecovered: Int = response.getInt("recovered")
                    val worldDeaths: Int = response.getInt("deaths")
                    worldRecoveredTV.text = worldRecovered.toString()
                    worldCasesTV.text = worldCases.toString()
                    worldDeathsTV.text = worldDeaths.toString()
                }
                catch (e:JSONException){
                    e.printStackTrace()
                }
            },{ _ ->
                    Toast.makeText(this, "Fail to get data", Toast.LENGTH_SHORT).show()

            })
        queue.add(request)
    }
}