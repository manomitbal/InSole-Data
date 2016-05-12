using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class Bar : MonoBehaviour {
	
	public float FillAmount;
	[SerializeField]
	private Image filler;
	[SerializeField]
	private Text value;
	GameObject player;
	SoccerShooter soccerShooter;

	// Use this for initialization
	void Start () {
		player = GameObject.Find ("FPSController");
		soccerShooter = player.GetComponent<SoccerShooter> ();
		FillAmount = soccerShooter.fillAmount;
		value.text = "Shooting Power: " + Mathf.Round(FillAmount*100) + "%";
	}
	
	// Update is called once per frame
	void Update () {
		filler.fillAmount = FillAmount;
		FillAmount = soccerShooter.fillAmount;
		value.text = "Shooting Power: " + Mathf.Round(FillAmount*100) + "%";
	}
}
