package com.unibo.seiot.smartdam.dammobileapp;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.ToggleButton;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.app.AppCompatDelegate;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.List;
import java.util.UUID;

import unibo.btlib.BluetoothChannel;
import unibo.btlib.BluetoothUtils;
import unibo.btlib.ConnectToBluetoothServerTask;
import unibo.btlib.ConnectionTask;
import unibo.btlib.RealBluetoothChannel;
import unibo.btlib.exceptions.BluetoothDeviceNotFound;

public class MainActivity extends AppCompatActivity {

    private BluetoothChannel btChannel;
    private boolean manualMode = false;
    private int activeButton = 0;
    private List<Button> buttons;
    private Switch sw;

    @Override
    protected void onCreate(final Bundle savedInstanceState) {
        AppCompatDelegate.setDefaultNightMode(AppCompatDelegate.MODE_NIGHT_NO);
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final BluetoothAdapter btAdapter = BluetoothAdapter.getDefaultAdapter();
        this.buttons = new ArrayList<>();

        if(btAdapter != null && !btAdapter.isEnabled()){
            startActivityForResult(new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE), Utils.bluetooth.ENABLE_BT_REQUEST);
        }
        initUI();
    }

    private void initUI() {

        findViewById(R.id.connect_bluetooth_button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    connectToBTServer();
                    Log.d(Utils.APP_LOG_TAG, "Try connect");
                } catch (BluetoothDeviceNotFound bluetoothDeviceNotFound) {
                    Log.d(Utils.APP_LOG_TAG, "Connect failed");
                    bluetoothDeviceNotFound.printStackTrace();

                }
            }
        });

        List<Integer> ids = Arrays.asList(R.id.bt_0,R.id.bt_20,R.id.bt_40,R.id.bt_60,R.id.bt_80,R.id.bt_100);

        for (final int id: ids) {
            final Button bt = findViewById(id);
            buttons.add(bt);
            bt.setEnabled(false);
            bt.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                if(manualMode) {
                    btChannel.sendMessage(
                            (String) bt.getText());
                    bt.setEnabled(false);
                    if (activeButton != 0) {
                        findViewById(activeButton).setEnabled(true);
                    }
                    activeButton = id;
                }
                }
            });
        };

        sw = findViewById(R.id.manual_mode_switch);
        sw.setEnabled(false);
        sw.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                manualMode = isChecked;
                for (Button bt : buttons) {
                    bt.setEnabled(isChecked);
                }
                if (isChecked) {
                    btChannel.sendMessage("M");
                } else {
                    btChannel.sendMessage("A");
                }
            }
        });
    }

    @Override
    protected void onStop() {
        super.onStop();

        btChannel.close();
    }

    @Override
    protected void onActivityResult(final int requestCode, final int resultCode, @Nullable final Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == Utils.bluetooth.ENABLE_BT_REQUEST && resultCode == RESULT_OK) {
            Log.d(Utils.APP_LOG_TAG, "Bluetooth enabled!");
        }

        if (requestCode == Utils.bluetooth.ENABLE_BT_REQUEST && resultCode == RESULT_CANCELED) {
            Log.d(Utils.APP_LOG_TAG, "Bluetooth not enabled!");
        }
    }

    private void connectToBTServer() throws BluetoothDeviceNotFound {
        final BluetoothDevice serverDevice = BluetoothUtils.getPairedDeviceByName(Utils.bluetooth.BT_DEVICE_ACTING_AS_SERVER_NAME);

        // !!! UTILIZZARE IL CORRETTO VALORE DI UUID
        final UUID uuid = BluetoothUtils.getEmbeddedDeviceDefaultUuid();
        //final UUID uuid = BluetoothUtils.generateUuidFromString(C.bluetooth.BT_SERVER_UUID);

        new ConnectToBluetoothServerTask(serverDevice, uuid, new ConnectionTask.EventListener() {
            @Override
            public void onConnectionActive(final BluetoothChannel channel) {

                ((TextView) findViewById(R.id.bluetooth_state_label)).setText(String.format("Status : connected to server on device %s",
                        serverDevice.getName()));

                btChannel = channel;
                btChannel.registerListener(new RealBluetoothChannel.Listener() {
                    @Override
                    public void onMessageReceived(String receivedMessage) {
                        handleMessage(receivedMessage);
                        Log.d(Utils.APP_LOG_TAG, receivedMessage);
                    }

                    @Override
                    public void onMessageSent(String sentMessage) {

                    }
                });
            }

            @Override
            public void onConnectionCanceled() {
                ((TextView) findViewById(R.id.bluetooth_state_label)).setText(String.format("Status : unable to connect, device %s not found!",
                        Utils.bluetooth.BT_DEVICE_ACTING_AS_SERVER_NAME));
            }
        }).execute();
    }
    //message S(1):dist(4):span(3)
    private void handleMessage(String receivedMessage) {
        String state = receivedMessage.split(":")[0];
        String distance = receivedMessage.split(":")[1];
        String span = receivedMessage.split(":")[2];

        this.handleState(state, distance, span);
    }

    private void handleState(String state, String distance, String span) {
        switch (state) {
            case "0": //Normal
                ((TextView) findViewById(R.id.current_state_label)).setText(R.string.state_normal);
                findViewById(R.id.current_state_label).setBackgroundResource(R.color.state_normal);
                ((TextView) findViewById(R.id.last_detection_title)).setText("");
                ((TextView) findViewById(R.id.last_detection)).setText("");
                ((TextView) findViewById(R.id.dam_span_title)).setText("");
                ((TextView) findViewById(R.id.dam_span)).setText("");
                this.sw.setChecked(false);
                this.sw.setEnabled(false);
                break;
            case "1": //Pre-Alarm
                ((TextView) findViewById(R.id.current_state_label)).setText(R.string.state_prealarm);
                findViewById(R.id.current_state_label).setBackgroundResource(R.color.state_prealarm);
                ((TextView) findViewById(R.id.last_detection_title)).setText(R.string.last_detection_title);
                ((TextView) findViewById(R.id.last_detection)).setText(distance);
                ((TextView) findViewById(R.id.dam_span_title)).setText("");
                ((TextView) findViewById(R.id.dam_span)).setText("");
                this.sw.setChecked(false);
                this.sw.setEnabled(false);
                break;
            case "2": //Alarm
                span += "%";
                ((TextView) findViewById(R.id.current_state_label)).setText(R.string.state_alarm);
                findViewById(R.id.current_state_label).setBackgroundResource(R.color.state_alarm);
                ((TextView) findViewById(R.id.last_detection_title)).setText(R.string.last_detection_title);
                ((TextView) findViewById(R.id.last_detection)).setText(distance);
                ((TextView) findViewById(R.id.dam_span_title)).setText(R.string.dam_span_title);
                ((TextView) findViewById(R.id.dam_span)).setText(span);
                this.sw.setEnabled(true);
                break;
        }
    }
}

