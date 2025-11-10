package com.ray.snxyjde;

import android.app.Dialog;
import android.content.Context;
import android.graphics.drawable.GradientDrawable;
import android.os.Bundle;
import android.util.Log;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

public class MyToolsDialog extends Dialog {

    private TextView outputView;
    private MainActivity activity;

    // 常用 DP 到 PX 的转换方法
    private int dpToPx(int dp) {
        return (int) TypedValue.applyDimension(
                TypedValue.COMPLEX_UNIT_DIP,
                dp,
                getContext().getResources().getDisplayMetrics()
        );
    }

    public MyToolsDialog(MainActivity activity) {
        super(activity);
        this.activity = activity;
    }

    public MyToolsDialog(Context context){
        super(context);
        if(context instanceof MainActivity){
            this.activity = (MainActivity) context;
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // --- 1. 根布局配置 ---
        LinearLayout layout = new LinearLayout(getContext());
        layout.setOrientation(LinearLayout.VERTICAL);

        // 外部内边距 (Padding)
        int padding = dpToPx(30);
        layout.setPadding(padding, padding, padding, padding);

        // 创建圆角背景：白色圆角
        GradientDrawable background = new GradientDrawable();
        background.setColor(0xFFFFFFFF); // 白色背景
        background.setCornerRadius(dpToPx(16)); // 圆角半径
        layout.setBackground(background);

        // --- 2. 顶部标题 ---
        TextView titleView = new TextView(getContext());
        titleView.setText("游戏工具");
        titleView.setTextSize(TypedValue.COMPLEX_UNIT_SP, 20); // 使用 SP 单位
        titleView.setGravity(Gravity.CENTER);
        titleView.setTextColor(0xFF12CDB0); // 主题色

        // 设置标题布局参数：MATCH_PARENT 宽度，并增加底部间距
        LinearLayout.LayoutParams titleLp = new LinearLayout.LayoutParams(
                LinearLayout.LayoutParams.MATCH_PARENT,
                LinearLayout.LayoutParams.WRAP_CONTENT);
        titleLp.bottomMargin = dpToPx(32); // 底部间距
        layout.addView(titleView, titleLp);


        // --- 3. 输出栏 (当前状态/速度) ---
        outputView = new TextView(getContext());
        outputView.setText("请选择操作...");
        outputView.setTextSize(TypedValue.COMPLEX_UNIT_SP, 16);
        outputView.setGravity(Gravity.CENTER);
        outputView.setTextColor(0xFF12CDB0);

        LinearLayout.LayoutParams outputLp = new LinearLayout.LayoutParams(
                LinearLayout.LayoutParams.MATCH_PARENT,
                LinearLayout.LayoutParams.WRAP_CONTENT);
        outputLp.bottomMargin = dpToPx(60); // 增加与按钮组的间距
        layout.addView(outputView, outputLp);


        // --- 4. 按钮组布局 (水平排列) ---
        LinearLayout buttonLayout = new LinearLayout(getContext());
        buttonLayout.setOrientation(LinearLayout.HORIZONTAL);
        buttonLayout.setGravity(Gravity.CENTER);

        LinearLayout.LayoutParams buttonLayoutLp = new LinearLayout.LayoutParams(
                LinearLayout.LayoutParams.MATCH_PARENT,
                LinearLayout.LayoutParams.WRAP_CONTENT);
        layout.addView(buttonLayout, buttonLayoutLp); // 将按钮组添加到主布局

        // 按钮通用背景：圆角主题色
        GradientDrawable buttonBackground = new GradientDrawable();
        buttonBackground.setColor(0xFF12CDB0);
        buttonBackground.setCornerRadius(dpToPx(8)); // 按钮圆角

        // 按钮通用布局参数：0 宽度 + 权重 1，实现平分宽度
        LinearLayout.LayoutParams buttonParams = new LinearLayout.LayoutParams(
                0, // 宽度为 0
                dpToPx(50), // 高度
                1f // 权重为 1
        );
        buttonParams.setMargins(dpToPx(5), 0, dpToPx(5), 0); // 按钮之间的间距

        // --- 5. 加速按钮 ---
        Button boostButton = new Button(getContext());
        boostButton.setText("加速");
        boostButton.setTextColor(0xFFFFFFFF); // 白色字体
        boostButton.setBackground(buttonBackground.getConstantState().newDrawable()); // 设置背景
        buttonLayout.addView(boostButton, buttonParams);

        // --- 6. 减速按钮 ---
        Button decelerateButton = new Button(getContext());
        decelerateButton.setText("减速");
        decelerateButton.setTextColor(0xFFFFFFFF);
        // 使用 newDrawable() 复制一份背景，防止两者共用一个Drawable对象导致问题
        decelerateButton.setBackground(buttonBackground.getConstantState().newDrawable());
        buttonLayout.addView(decelerateButton, buttonParams);

        // 设置Dialog的内容视图
        setContentView(layout);

        // --- 7. 配置 Dialog Window 样式 ---
        if (getWindow() != null) {
            // 设置背景透明，以便只显示自定义的 layout 背景（圆角）
            getWindow().setBackgroundDrawableResource(android.R.color.transparent);

            // 设置宽度为 MATCH_PARENT，高度为 WRAP_CONTENT
            getWindow().setLayout(
                    ViewGroup.LayoutParams.MATCH_PARENT,
                    ViewGroup.LayoutParams.WRAP_CONTENT
            );
            // 增加左右边距，让 Dialog 不会贴着屏幕边缘
            getWindow().getDecorView().setPadding(dpToPx(30), 0, dpToPx(30), 0);
        }

        // --- 8. 设置按钮点击事件 (Native 调用) ---
        boostButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (activity != null) {
                    try {
                        activity.callBoost(); // 调用 Native 方法
                        outputView.setText("当前：加速！(Native调用成功)");
                        Log.d("testDialog", "Boost button clicked, calling Native callBoost()");
                    } catch (Exception e) {
                        Log.e("testDialog", "Error on Boost button click: " + e.getMessage());
                    }
                }
            }
        });

        decelerateButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (activity != null) {
                    try {
                        activity.callDecelerate(); // 调用 Native 方法
                        outputView.setText("当前：减速！(Native调用成功)");
                        Log.d("testDialog", "Decelerate button clicked, calling Native callDecelerate()");
                    } catch (Exception e) {
                        Log.e("testDialog", "Error on Decelerate button click: " + e.getMessage());
                    }
                }
            }
        });
    }
}