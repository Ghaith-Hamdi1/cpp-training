package com.cppquiz

import android.Manifest
import android.app.AlarmManager
import android.app.NotificationChannel
import android.app.NotificationManager
import android.app.PendingIntent
import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.content.pm.PackageManager
import android.os.Build
import androidx.core.app.NotificationCompat
import androidx.core.content.ContextCompat
import java.util.Calendar
import java.util.TimeZone

/** The optional daily reminder: one notification a day, skipped when the daily goal is already met. */
object Reminder {
    private const val CHANNEL = "daily_reminder"
    private const val REQUEST = 7

    private fun prefs(c: Context) = c.getSharedPreferences("cppquiz", Context.MODE_PRIVATE)

    fun enabled(c: Context) = prefs(c).getBoolean("reminderOn", false)
    fun hour(c: Context) = prefs(c).getInt("reminderHour", 18)

    fun save(c: Context, on: Boolean, hour: Int) {
        prefs(c).edit().putBoolean("reminderOn", on).putInt("reminderHour", hour).apply()
        reschedule(c)
    }

    private fun pending(c: Context): PendingIntent =
        PendingIntent.getBroadcast(c, REQUEST, Intent(c, ReminderReceiver::class.java), PendingIntent.FLAG_IMMUTABLE)

    /** Cancels the alarm and, when the reminder is on, sets it again for the next chosen hour. */
    fun reschedule(c: Context) {
        val alarm = c.getSystemService(Context.ALARM_SERVICE) as AlarmManager
        alarm.cancel(pending(c))
        if (!enabled(c)) return
        val first = Calendar.getInstance().apply {
            set(Calendar.HOUR_OF_DAY, hour(c)); set(Calendar.MINUTE, 0); set(Calendar.SECOND, 0); set(Calendar.MILLISECOND, 0)
            if (timeInMillis <= System.currentTimeMillis()) add(Calendar.DAY_OF_MONTH, 1)
        }.timeInMillis
        alarm.setInexactRepeating(AlarmManager.RTC_WAKEUP, first, AlarmManager.INTERVAL_DAY, pending(c))
    }

    fun canNotify(c: Context): Boolean =
        Build.VERSION.SDK_INT < 33 ||
            ContextCompat.checkSelfPermission(c, Manifest.permission.POST_NOTIFICATIONS) == PackageManager.PERMISSION_GRANTED

    /** Same day arithmetic as Store, so "goal met today" means the same thing in both places. */
    private fun today(): Long = (System.currentTimeMillis() + TimeZone.getDefault().rawOffset) / 86_400_000L

    fun notifyIfNeeded(c: Context) {
        if (!enabled(c) || !canNotify(c)) return
        val p = prefs(c)
        val goal = p.getInt("goal", 1)
        val done = if (p.getLong("countDay", -1L) == today()) p.getInt("todayCount", 0) else 0
        if (done >= goal) return
        val streak = if (p.getLong("lastDay", -1L) >= today() - 1) p.getInt("streak", 0) else 0

        val nm = c.getSystemService(Context.NOTIFICATION_SERVICE) as NotificationManager
        if (Build.VERSION.SDK_INT >= 26) {
            nm.createNotificationChannel(NotificationChannel(CHANNEL, "Daily reminder", NotificationManager.IMPORTANCE_DEFAULT))
        }
        val open = PendingIntent.getActivity(c, 0, Intent(c, MainActivity::class.java), PendingIntent.FLAG_IMMUTABLE)
        val n = NotificationCompat.Builder(c, CHANNEL)
            .setSmallIcon(android.R.drawable.ic_popup_reminder)
            .setContentTitle("Your C++ lesson is waiting")
            .setContentText(
                if (streak > 0) "Finish ${goal - done} more today to keep your $streak-day streak."
                else "Finish ${goal - done} lesson${if (goal - done == 1) "" else "s"} today to start a streak.",
            )
            .setContentIntent(open)
            .setAutoCancel(true)
            .build()
        nm.notify(REQUEST, n)
    }
}

class ReminderReceiver : BroadcastReceiver() {
    override fun onReceive(context: Context, intent: Intent) {
        Reminder.notifyIfNeeded(context)
    }
}

/** Alarms are lost on reboot, so the reminder is set again when the phone has started. */
class BootReceiver : BroadcastReceiver() {
    override fun onReceive(context: Context, intent: Intent) {
        if (intent.action == Intent.ACTION_BOOT_COMPLETED) Reminder.reschedule(context)
    }
}
