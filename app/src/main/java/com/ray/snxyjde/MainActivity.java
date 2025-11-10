package com.ray.snxyjde;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.TextView;

import com.ray.snxyjde.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("snxyjde");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        MyBoostBall boostBall = new MyBoostBall(this);
        ViewGroup.LayoutParams params = new FrameLayout.LayoutParams(200,200);
        boostBall.setLayoutParams(params);

        binding.getRoot().addView(boostBall);
    }

    public native void callBoost();

    public native void callDecelerate();

}