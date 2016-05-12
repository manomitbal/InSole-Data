using UnityEngine;
using System.Collections;

public class leftFootMove : MonoBehaviour {
	public Vector3 left_accelerate = new Vector3 ();
	//public Vector3 left_orientation = new Vector3 ();
	Rigidbody left_foot_rb;
	Vector3 initial_left_foot_velocity = new Vector3();
	Vector3 final_left_foot_velocity = new Vector3(0,0,0);
	GameObject right_foot;
	Vector3 new_pos = new Vector3();
	bool stop;
	float color;
	public Renderer rend;

	// Use this for initialization
	void Start () {
		right_foot = GameObject.FindGameObjectWithTag ("RightFoot");
		left_foot_rb = GetComponent<Rigidbody> ();
		rend = GetComponentInChildren <Renderer> ();
	}
	
	// Update is called once per frame
	void Update () {
		GameObject fps = GameObject.Find("FPSwithFeet");
		DataListener datalistener = fps.GetComponent<DataListener> ();
		stop = datalistener.stop;
		color = datalistener.color;
		left_accelerate.x = datalistener.left_accelerate.x*10f;
		//left_accelerate.x = 0f;
		left_accelerate.y = datalistener.left_accelerate.y*5f;
		left_accelerate.z = datalistener.left_accelerate.z*10f;

		//left_orientation.x = datalistener.left_orientation.x;
		//left_orientation.y = datalistener.left_orientation.y;
		//left_orientation.z = datalistener.left_orientation.z;

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

		//move left foot
		if (!stop) {
			initial_left_foot_velocity = final_left_foot_velocity;
			final_left_foot_velocity = initial_left_foot_velocity + left_accelerate * Time.deltaTime;
			left_foot_rb.velocity = final_left_foot_velocity;
		} else {
			left_foot_rb.velocity = new Vector3 (0, 0, 0);
			final_left_foot_velocity = new Vector3 (0, 0, 0);
			Vector3 pos = transform.position;
			transform.position = new Vector3 (pos.x, 0.34f, pos.z);
		}
		//Debug.Log ("LEFT FOOT SPEED:" + left_foot_rb.velocity);
		//Debug.Log ("left_acceleration:" + left_accelerate);
		//correct distance if two feet too far
		/*if (Mathf.Abs (transform.position.x - right_foot.transform.position.x) > 2f) {
			if (transform.position.x > right_foot.transform.position.x) {
				new_pos.x = right_foot.transform.position.x + 2f;
			} else {
				new_pos.x = right_foot.transform.position.x - 2f;
			}
		}
		if (Mathf.Abs (transform.position.y - right_foot.transform.position.y) > 1f) {
			if (transform.position.y > right_foot.transform.position.y) {
				new_pos.y = right_foot.transform.position.y + 1f;
			} else {
				new_pos.y = right_foot.transform.position.y - 1f;
			}
		}
		if (Mathf.Abs (transform.position.z - right_foot.transform.position.z) > 2f) {
			if (transform.position.z > right_foot.transform.position.z) {
				new_pos.z = right_foot.transform.position.z + 2f;
			} else {
				new_pos.z = right_foot.transform.position.z - 2f;
			}
		}
		transform.position = new_pos;
*/
	}
}
