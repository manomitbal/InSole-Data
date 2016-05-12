using UnityEngine;
using System.Collections;

public class footMoveController : MonoBehaviour {
	GameObject left_foot;
	GameObject right_foot;

	void Start () {
		left_foot = GameObject.FindGameObjectWithTag ("LeftFoot");
		right_foot = GameObject.FindGameObjectWithTag ("RightFoot");
	}
	
	// Update is called once per frame
	//void Update () {
		
	//	transform.position = (left_foot.transform.position + right_foot.transform.position) / 2.0f;
	//}

	void FixedUpdate () {
		Vector3 pos = transform.position;
		transform.position = new Vector3 ((left_foot.transform.position.x + right_foot.transform.position.x) / 2f, left_foot.transform.position.y+1.46f, (left_foot.transform.position.z + right_foot.transform.position.z) / 2f);
	}
}
