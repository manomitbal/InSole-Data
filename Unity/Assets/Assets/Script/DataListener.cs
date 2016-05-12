using UnityEngine;
using System.Collections;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.IO;
using System.Text;

public class DataListener : MonoBehaviour {

    private Socket _serverSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
    private byte[] _receiveBuffer = new byte[1024];
    private ArrayList _messageBuffer = new ArrayList();
    private Socket _dataSocket;

	public Vector3 left_orientation = new Vector3();
	public Vector3 right_orientation = new Vector3();
	public Vector3 left_accelerate_raw = new Vector3();
	public Vector3 right_accelerate_raw = new Vector3();
	Vector3 left_accelerate_prev = new Vector3 (0,0,0);
	Vector3 right_accelerate_prev = new Vector3(0,0,0);
	public Vector3 left_accelerate = new Vector3();
	public Vector3 right_accelerate = new Vector3();
	public bool stop;
	public float color;

    private void WaitForClient() {
        try {
           _serverSocket.Bind(new IPEndPoint(IPAddress.Any, 6000));
           _serverSocket.Listen(1);

           Debug.Log("Waiting for client connection...");
           _dataSocket = _serverSocket.Accept();
           Debug.Log("Connected to client.");
        }
        catch (SocketException e) {
            Debug.Log(e.ToString());
        }
    }

    string array_list_to_string(ArrayList arr) {
        string ret = "";
        for (int i = 0; i < arr.Count; i++) {
            ret += System.Convert.ToChar(arr[i]);
        }
        return ret;
    }

    // Collect data in _messageBuffer until '\n' is received because this 
    // signifies the end of a message
    private void UpdateReceivedData(byte[] buf, int len) {
        for (int i = 0; i < len; i++) {
            if (buf[i] == '\n') {
                // Message Complete. Message buffer contains a complete data point
                Debug.Log("Received a complete message.");
                string message = array_list_to_string(_messageBuffer);
                HandleMessage(message);
                _messageBuffer.Clear();
            } else {
                _messageBuffer.Add(buf[i]);
            }
        }
    }

	// Use this for initialization
	void Start () {
        WaitForClient();
	}
	
	// Update is called once per frame
	void Update () {
//		Debug.Log("Data available!");
        // Check if there is data in socket
        if (_dataSocket.Available > 0) {
       //     Debug.Log("Data available!");
            int toRead;
            // Read either the entire amount available, or the size of the receive buffer. Whichever is smaller.
            if (_dataSocket.Available > _receiveBuffer.Length) {
                toRead = _receiveBuffer.Length;
            } else {
                toRead = _dataSocket.Available;
            }
            int bytesReceived = _dataSocket.Receive(_receiveBuffer, toRead, SocketFlags.None);
            UpdateReceivedData(_receiveBuffer, bytesReceived);
        }
	}

    void HandleMessage(string message) {
		float thresh;
		thresh=0.2f;
		Debug.Log ("MESSAGE: " + message);
        // message should be a string with the following format:
        // left_roll left_pitch left_yaw right_roll right_pitch right_yaw accX accY accZ
        char delimiterChars = ' ';
        string[] measurements = message.Split(' ');

		//Debug.Log (measurements.Length);
		/*
		for (int i = 0; i < measurements.Length-1; i++) {
			Debug.Log ("DATA INDEX: "+ i + "VALUE: " + measurements[i]);
		}
	*/
		//Debug.Log ("length: " + message.Length+ " "+measurements[0]);
		if (measurements.Length != 7) {//changed from 8!
            Debug.Log("Message in incorrect format.");
            return;
        	}
		//for (int i = 0; i < measurements.Length; i++) {
		//	Debug.Log(measurements[i]);
		//}
        left_orientation.x = -1 * System.Convert.ToSingle(measurements[1]);
        left_orientation.y = -1 * System.Convert.ToSingle(measurements[2]);
        left_orientation.z = -1 * System.Convert.ToSingle(measurements[0]);

        right_orientation.x = -1 * System.Convert.ToSingle(measurements[1]);
        right_orientation.y = -1 * System.Convert.ToSingle(measurements[2]);
        right_orientation.z = -1 * System.Convert.ToSingle(measurements[0]);

		left_accelerate_raw.x = System.Convert.ToSingle(measurements[4]);
		left_accelerate_raw.y = System.Convert.ToSingle(measurements[6]);
		left_accelerate_raw.z = System.Convert.ToSingle(measurements[5]);

		right_accelerate_raw.x =System.Convert.ToSingle(measurements[4]);
		right_accelerate_raw.y =System.Convert.ToSingle(measurements[6]);
		right_accelerate_raw.z =System.Convert.ToSingle(measurements[5]);

		color = System.Convert.ToSingle (measurements [3]);
		//System.Console.WriteLine("hello");

        GameObject left_foot = GameObject.FindGameObjectWithTag("LeftFoot");
        left_foot.transform.eulerAngles = left_orientation;

        GameObject right_foot = GameObject.FindGameObjectWithTag("RightFoot");
        right_foot.transform.eulerAngles = right_orientation;

		Debug.Log ("right orientation:" + right_orientation);
		//Debug.Log ("ACCELERATION VECTOR BEFORE FILTER-----: "+right_accelerate);

		//Debug.Log ("X BEFORE FILTER:" +left_accelerate_raw.x);
		if (Mathf.Abs(left_accelerate_raw.x) < 0.1f) {
			left_accelerate.x = 0f;

		} else {
			left_accelerate.x = left_accelerate_raw.x;

		}

		if (Mathf.Abs(right_accelerate_raw.x) < 0.1f) {
			right_accelerate.x = 0f;

		} else {
			right_accelerate.x = right_accelerate_raw.x;

		}
		//Debug.Log ("Z BEFORE FILTER:" +left_accelerate_raw.z);
		//if (stop = false) {
		if (Mathf.Abs (left_accelerate_raw.z) < 0.1f) {
				left_accelerate.z = 0f;
				
		} else {
				left_accelerate.z = left_accelerate_raw.z;
				
		}

		if (Mathf.Abs (right_accelerate_raw.z) < 0.1f) {
			right_accelerate.z = 0f;

		} else {
			right_accelerate.z = right_accelerate_raw.z;

		}
		if (Mathf.Abs (left_accelerate_raw.y - 2.7f) < 0.1f || left_accelerate_raw.y<=0) {
				left_accelerate.y = 0f;
				
			} else {
				left_accelerate.y = left_accelerate_raw.y - 2.7f;
				
			}

		if (Mathf.Abs (right_accelerate_raw.y - 2.7f) < 0.1f || right_accelerate_raw.y<=0) {
			right_accelerate.y = 0f;

		} else {
			right_accelerate.y = right_accelerate_raw.y - 2.7f;

		}
		//}
			
		//left_accelerate.y = left_accelerate_raw.y - 2.7f;
		//right_accelerate.y = right_accelerate_raw.y - 2.7f;
	    /*
		if ((left_accelerate.x < left_accelerate_prev.x - 0.5f) || (left_accelerate.x > left_accelerate_prev.x + 0.5f)) {
			//REJECT NEW ACCELERATION
			//Debug.Log ("X-- ACCELERATION REJECTED!!!!: "+ left_accelerate.x);
			if (left_accelerate.x != 0) {
				left_accelerate.x = left_accelerate_prev.x;
			}
		}

		if ((left_accelerate.y < left_accelerate_prev.y - 0.8f) || (left_accelerate.y > left_acc	elerate_prev.y + 0.5f)) {
			//REJECT NEW ACCELERATION
			//Debug.Log ("Y-- ACCELERATION REJECTED!!!!: "+ left_accelerate.y);
			if (left_accelerate.y != 0) {
				left_accelerate.y = left_accelerate_prev.y;
			}
		}

		if ((left_accelerate.z < left_accelerate_prev.z - 0.5f) || (left_accelerate.z > left_accelerate_prev.z + 0.5f)) {
			//REJECT NEW ACCELERATION
			//Debug.Log ("Z-- ACCELERATION REJECTED!!!!: "+ left_accelerate.z);
			if (left_accelerate.z != 0) {
				left_accelerate.z = left_accelerate_prev.z;
			}
		}
		*/
		//Debug.Log ("ACCELERATION: "+right_accelerate+ " ACCELERATION PREVIOUS: "+right_accelerate_prev);

		if (left_accelerate.x == 0f && left_accelerate.y == 0f && left_accelerate.z == 0f) {
			stop = true;
		}
		//SMALL FILTER SO WE ARE JUST ORIENTING WHEN THE FOOT SHOULDN'T MOVE.

		/*else if ((left_accelerate.x > left_accelerate_prev.x - 0.4f && left_accelerate.x < left_accelerate_prev.x + 0.4f) 
			&& (left_accelerate.z > left_accelerate_prev.z - 0.4f && left_accelerate.z < left_accelerate_prev.z + 0.4f)  
			&& (left_accelerate.y > left_accelerate_prev.y - 0.4f && left_accelerate.y < left_accelerate_prev.y + 0.4f)){
			//&& (left_accelerate.x>0.09f)){
			stop = true;
		}*/

		else {
			stop = false; //FOOT MOVING
		}

		right_accelerate = left_accelerate;
	
		//Debug.Log ("right accelerate: "+right_accelerate);

		//left_accelerate_prev = left_accelerate;
		//right_accelerate_prev = right_accelerate;*/
    }
}
