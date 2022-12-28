<script lang="ts">
  import type { Wifi } from "../../../../shared/@types/Wifi";
  import Modal from '../../../../shared/components/Modal/index.svelte'
  import Button, { Label } from '@smui/button';
  import {Icon} from '@smui/common';
  import IconButton from '@smui/icon-button'
  import Textfield from '@smui/textfield';

  export let wifi:Wifi;
  export let isOpened=false;
  const closeModal=()=>isOpened=false;

  let showPassword=false;
  const switchPasswordVisibility=()=>showPassword=!showPassword;

  let password=""

  const connect=()=>console.log("Conectando ao wifi kkk");
</script>

<Modal bind:isOpened={isOpened}>
  <div>
    <h4>Conectar à rede {wifi.name}</h4>
    <p>Intensidade do sinal: {wifi.signal}</p>
    <p>
      <Textfield type={showPassword?"text":"password"} bind:value={password} label="Senha" ></Textfield>
      <IconButton on:click={switchPasswordVisibility}><Icon class="material-icons">visibility</Icon></IconButton></p>
    <p>
      <Button variant="text" on:click={closeModal}><Label>Cancelar</Label></Button>
      <Button variant="raised" on:click={connect}><Label>Conectar</Label></Button>
    </p>
  </div>
</Modal>