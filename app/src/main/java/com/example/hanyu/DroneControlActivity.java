package com.example.hanyu.bluetoothdrone;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import java.io.IOException;
import java.util.UUID;

public class DroneControlActivity extends AppCompatActivity {
    Button forward;
    Button backward;
    Button right;
    Button left;
    Button disconnect;
    BluetoothAdapter btAdapter = null;
    BluetoothSocket btSocket = null;
    private boolean isBtConnected = false;
    static final UUID uuidAddress = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    static final String pulseStrength = "1000";
    String address = null;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Intent intent = getIntent();
        address = intent.getStringExtra(MainActivity.EXTRA_ADDRESS);
        setContentView(R.layout.activity_drone_control);

        forward = (Button)findViewById(R.id.forward);
        backward = (Button)findViewById(R.id.backward);
        right = (Button)findViewById(R.id.right);
        left = (Button)findViewById(R.id.left);
        disconnect = (Button)findViewById(R.id.disconnect);

        new ConnectBt().execute();

        forward.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                initiateCommand();
                forward();
            }
        });

        backward.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                initiateCommand();
                backward();
            }
        });

        right.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                initiateCommand();
                right();
            }
        });

        left.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                initiateCommand();
                left();
            }
        });

    }

    private void initiateCommand() {
        if (btSocket != null) {
            try {
                btSocket.getOutputStream().write("1".toString().getBytes());
            }
            catch (IOException e) {
                Toast.makeText(getApplicationContext(), "Error", Toast.LENGTH_SHORT).show();
            }
        }
    }

    private void forward() {
        if (btSocket != null) {
            try {
                btSocket.getOutputStream().write(pulseStrength.toString().getBytes());
            }
            catch (IOException e) {
                Toast.makeText(getApplicationContext(), "Error", Toast.LENGTH_SHORT).show();
            }
        }
    }

    private void backward() {}

    private void right() {}

    private void left() {}

    private class ConnectBt extends AsyncTask<Void, Void, Void> {
        private boolean ConnectSuccess = true;
        @Override
        protected Void doInBackground(Void... devices) {
            try {
                if (btSocket == null || !isBtConnected) {
                    btAdapter = BluetoothAdapter.getDefaultAdapter();
                    BluetoothDevice mobileBtDevice = btAdapter.getRemoteDevice(address);
                    btSocket = mobileBtDevice.createInsecureRfcommSocketToServiceRecord(uuidAddress);
                    btSocket.connect();
                }
            }
            catch (IOException e) {
                ConnectSuccess = false;
            }
            return null;
        }

        @Override
        protected void onPostExecute(Void result) {
            super.onPostExecute(result);
            if (ConnectSuccess) {
                Toast.makeText(getApplicationContext(), "Bluetooth Connected Successfully", Toast.LENGTH_LONG).show();
            } else {
                Toast.makeText(getApplicationContext(), "Bluetooth Not Connected Successfully", Toast.LENGTH_SHORT).show();
            }
        }
    }
}
