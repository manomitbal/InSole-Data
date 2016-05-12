using UnityEngine;
using System.Collections;

public class Ethan : MonoBehaviour {

	public Animator anim;
	private float inputHori;
	private float inputVerti;
	private bool run;
	private bool jump;
	private bool shoot;
	public bool shootDone;
	private bool HasBall;
	SoccerShooter soccerShooter;

	void Start () {
		anim = GetComponent <Animator> ();
		run = false;
		shootDone = false;

		soccerShooter = GetComponentInParent<SoccerShooter> ();
		HasBall = soccerShooter.hasBall;
	}
	
	// Update is called once per frame
	void Update () {
		HasBall = soccerShooter.hasBall;

		inputHori = Input.GetAxis ("Horizontal");
		inputVerti = Input.GetAxis ("Vertical");
		anim.SetFloat ("inputH", inputHori);
		anim.SetFloat ("inputV", inputVerti);

		if (Input.GetKey (KeyCode.LeftShift)) {
			run = true;
		} else {
			run = false;
		}
		anim.SetBool ("run", run);

		if (Input.GetKey ("space")) {
			jump = true;
		} else {
			jump = false;
		}
		anim.SetBool ("jump", jump);

		if (Input.GetMouseButtonDown (0) && HasBall) {
			shoot = true;
		} else {
			shoot = false;
		}
		anim.SetBool ("shoot", shoot);

	}

	public void hasShootDone(){
		shootDone = true;
	}
}
