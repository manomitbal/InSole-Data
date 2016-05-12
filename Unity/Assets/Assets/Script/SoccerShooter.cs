using UnityEngine;
using System.Collections;

public class SoccerShooter : MonoBehaviour {

	GameObject soccer;
	GameObject soccerHolder;
	Rigidbody rb;
	public float SoccerSpeed=30f;
	private float soccerMaxSpeed = 50f;
	public bool hasBall=true;
	public float fillAmount;
	private bool shootTrigger;
	Ethan ethan;
	// Use this for initialization
	void Start () {
		soccerHolder = transform.Find ("soccerHolder").gameObject;
		soccer = soccerHolder.transform.Find ("soccer").gameObject;
		rb = soccer.GetComponent<Rigidbody> ();
		fillAmount = SoccerSpeed / soccerMaxSpeed;

		ethan = GetComponentInChildren<Ethan> ();
		shootTrigger = ethan.shootDone;
	}

	// Update is called once per frame
	void Update () {
		shootTrigger = ethan.shootDone;

		if (hasBall && shootTrigger) {
			ShootSoccer ();
		}

		if (Input.GetKeyDown ("r") && hasBall == false) {
			ResetSoccer ();
		}
		if (Input.GetKey ("i") && SoccerSpeed < 50f) {
			SoccerSpeed += 0.1f;
		}
		if (Input.GetKey ("o") && SoccerSpeed > 0.5f) {
			SoccerSpeed -= 0.1f;
		}
		fillAmount = SoccerSpeed / soccerMaxSpeed;
	}

	void OnControllerColliderHit (ControllerColliderHit hit){

		if (hit.gameObject.name == "soccer" && hasBall == false) {
			Debug.Log ("hit");
			ResetSoccer ();
		}
	}

	public void ResetSoccer(){
		hasBall = true;
		rb.isKinematic = true;
		soccer.transform.parent = soccerHolder.transform;
		soccer.transform.localPosition = new Vector3 (0, 0, 0);
	}

	public void ShootSoccer() {
		shootTrigger = false;
		ethan.shootDone = false;
		hasBall = false;
		soccer.transform.parent = null;
		rb.isKinematic = false;
		rb.velocity = Camera.main.transform.forward * SoccerSpeed;
	}

}
