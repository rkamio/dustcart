<template>
  <div>
    <!-- TODO:中央寄せ margin-left:auto;-->
    <table>
      <tbody>
        <tr>
          <td></td>
          <td>
            <v-icon
              v-if="!forward.on"
              x-large
              @mousedown="moving('forward')"
              @mouseup="reset('forward')"
              @touchstart="moving('forward')"
              @touchend="reset('forward')"
            >
              mdi-arrow-up-bold-box-outline
            </v-icon>
            <v-icon v-else x-large>
              mdi-arrow-up-bold-box
            </v-icon>
          </td>
          <td></td>
        </tr>
        <tr>
          <td>
            <v-icon
              v-if="!left.on"
              x-large
              @mousedown="moving('left')"
              @mouseup="reset('left')"
              @touchstart="moving('left')"
              @touchend="reset('left')"
            >
              mdi-arrow-left-bold-box-outline
            </v-icon>
            <v-icon v-else x-large>
              mdi-arrow-left-bold-box
            </v-icon>
          </td>
          <td>
            <v-icon x-large>
              mdi-apple
              <!-- mdi-nintendo-switch -->
            </v-icon>
          </td>
          <td>
            <v-icon
              v-if="!right.on"
              x-large
              @mousedown="moving('right')"
              @mouseup="reset('right')"
              @touchstart="moving('right')"
              @touchend="reset('right')"
            >
              mdi-arrow-right-bold-box-outline
            </v-icon>
            <v-icon v-else x-large>
              mdi-arrow-right-bold-box
            </v-icon>
          </td>
        </tr>
        <tr>
          <td></td>
          <td>
            <v-icon
              v-if="!back.on"
              x-large
              @mousedown="moving('back')"
              @mouseup="reset('back')"
              @touchstart="moving('back')"
              @touchend="reset('back')"
            >
              mdi-arrow-down-bold-box-outline
            </v-icon>
            <v-icon v-else x-large>
              mdi-arrow-down-bold-box
            </v-icon>
          </td>
          <td></td>
        </tr>
      </tbody>
    </table>
  </div>
</template>

<script>
const INTERVAL = 1

export default {
  // timeはミリ秒; back=down, forward=up
  data() {
    return {
      // TODO: force: {on: false, time:0, timerObj, x:0, y:0}だけにして、引数で(x,y)あげる？
      forward: { on: false, time: 0, timerObj: null },
      back: { on: false, time: 0, timerObj: null },
      left: { on: false, time: 0, timerObj: null },
      right: { on: false, time: 0, timerObj: null }
    }
  },
  methods: {
    countTime(direction) {
      this[direction].time += INTERVAL
    },
    moving(direction) {
      const self = this // NOTE: 関数入るとthisの参照先が変わるため、ここで取っておく。
      this[direction].timerObj = setInterval(function() {
        self.countTime(direction)
        console.log(
          `pushing ${direction} button: elapsed ${self[direction].time}`
        )
        // ここでサーバーへコマンドを送信
      }, INTERVAL)
      this[direction].on = true
    },
    reset(direction) {
      clearInterval(this[direction].timerObj)
      this[direction].on = false
      this[direction].time = 0
    }
  }
}
</script>
