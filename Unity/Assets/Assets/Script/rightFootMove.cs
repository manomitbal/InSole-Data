using UnityEngine;
using System.Collections;

public class rightFootMove : MonoBehaviour {
	public Vector3 right_accelerate = new Vector3 ();
	Rigidbody right_foot_rb;
	Vector3 initial_right_foot_velocity = new Vector3();
	Vector3 final_right_foot_velocity = new Vector3(0,0,0);
	GameObject left_foot;
	Vector3 new_pos = new Vector3();
	bool stop;
	float color;
	public Renderer rend;

	// Use this for initialization
	void Start () {
		left_foot = GameObject.FindGameObjectWithTag ("LeftFoot");
		right_foot_rb = GetComponent<Rigidbody> ();
		rend = GetComponentInChildren<Renderer> ();
	}
	
	// Update is called once per frame
	void Update () {
		GameObject fps = GameObject.Find("FPSwithFeet");
		DataListener datalistener = fps.GetComponent<DataListener> ();
		stop = datalistener.stop;
		color = datalistener.color;
		right_accelerate.x = datalistener.right_accelerate.x*10f;
		//right_accelerate.x = 0f;
		right_accelerate.y = datalistener.right_accelerate.y*5f;
		right_accelerate.z = datalistener.right_accelerate.z*10f;

		//color
		if (color == 2f) {
			rend.material.color = Color.red;
		} else if (color == 1f) {
			rend.material.color = Color.yellow;
		}
		else {
			rend.material.color = Color.white;
		}
	
		new_pos = transform.position;

		//move right foot
		if (!stop) {
			initial_right_foot_velocity = final_right_foot_velocity;
			final_right_foot_velocity = initial_right_foot_velocity + right_accelerate * Time.deltaTime;
			right_foot_rb.velocity = final_right_foot_velocity;
		} else {
			right_foot_rb.velocity = new Vector3 (0, 0, 0);
			final_right_foot_velocity = new Vector3 (0, 0, 0);
			Vector3 pos = transform.position;
			transform.position = new Vector3 (pos.x, 0.34f, pos.z);
		}
		//Debug.Log ("right foot velocity" + right_foot_rb.velocity);
		//Debug.Log ("right foot acceleration" + right_accelerate);
		//Debug.Log ("right FOOT SPEED:" + right_foot_rb.velocity);
		// correct disdance if two feet too far
		/*if (Mathf.Abs (transform.position.x - left_foot.transform.position.x) > 2f) {
			if (transform.position.x > left_foot.transform.position.x) {
				new_pos.x = left_foot.transform.position.x + 2f;
			} else {
				new_pos.x = left_foot.transform.position.x - 2f;
			}
		}
		if (Mathf.Abs (transform.position.y - left_foot.transform.position.y) > 1f) {
			if (transform.position.y > left_foot.transform.position.y) {
				new_pos.y = left_foot.transform.position.y + 1f;
			} else {
				new_pos.y = left_foot.transform.position.y - 1f;
			}
		}
		if (Mathf.Abs (transform.position.z - left_foot.transform.position.z) > 2f) {
			if (transform.position.z > left_foot.transform.position.z) {
				new_pos.z = left_foot.transform.position.z + 2f;
			} else {
				new_pos.z = left_foot.transform.position.z - 2f;
			}
		}
		transform.position = new_pos;
*/
	}
}
