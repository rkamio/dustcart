<template>
  <v-container>
    <v-row>
      <v-col cols="12">
        <h3>こっくぴっと</h3>
        <v-card>
          <v-tabs v-model="tab" background-color="primary" dark>
            <v-tab>
              カメラ
            </v-tab>
            <v-tab>
              赤外線
            </v-tab>
            <v-spacer></v-spacer>
            <!-- <v-btn small color="red accent-4" elevation="24" fab>
              <v-icon>
                mdi-skull-crossbones
              </v-icon>
            </v-btn> -->
            <v-btn
              color="red accent-4"
              fab
              small
              style="position:absolute;bottom:0;right:0;"
            >
              <v-icon>
                mdi-skull-crossbones
              </v-icon>
            </v-btn>
          </v-tabs>

          <v-tabs-items v-model="tab">
            <v-tab-item>
              <v-card flat>
                <VisualStreamer />

                <v-card-text>
                  <CarController />
                </v-card-text>
              </v-card>
            </v-tab-item>

            <v-tab-item>
              <v-card flat>
                <VisualStreamer />
                <v-card-text>
                  <CarController />
                </v-card-text>
              </v-card>
            </v-tab-item>
          </v-tabs-items>
        </v-card>
      </v-col>
    </v-row>
  </v-container>
</template>

<script>
import CarController from '../components/CarController.vue'
import VisualStreamer from '../components/VisualStreamer.vue'

export default {
  components: {
    CarController,
    VisualStreamer
  },
  data() {
    return {
      tab: null
    }
  }
}
</script>
