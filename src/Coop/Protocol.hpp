#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace AliceCoopProtocol
{
	constexpr std::uint32_t Magic = 0x504F4341; // "ACOP" in little-endian byte order.
	// Deliberately left at 29 even though a packet type was added. The relay
	// server is built separately from its own copy of this header and checks
	// this number on every datagram, so bumping it here quietly turns every
	// packet into a malformed one until the relay is rebuilt too. The new type
	// is purely additive - a build that does not know it simply ignores it.
	constexpr std::uint16_t Version = 29;
	constexpr std::uint16_t DefaultPort = 27018;
	constexpr std::size_t MaxDatagramSize = 1024;
	constexpr std::size_t MaxAnimationSequences = 12;
	constexpr std::size_t MaxAnimationBlends = 20;
	constexpr std::size_t MaxSharedEnemies = 10;
	constexpr std::size_t SaveSyncFileCount = 2;
	constexpr std::size_t SaveSyncChunkBytes = 900;

	enum class PacketType : std::uint16_t
	{
		Hello = 1,
		Welcome = 2,
		State = 3,
		PeerLeft = 4,
		Ping = 5,
		Pong = 6,
		ClientCommand = 7,
		HostSnapshot = 8,
		AnimationGraph = 9,
		ProjectileEvent = 10,
		SharedWorldEvent = 11,
		SaveSyncRequest = 12,
		SaveSyncManifest = 13,
		SaveSyncChunk = 14,
		SaveSyncAck = 15,
	};

	enum class SaveSyncFileKind : std::uint8_t
	{
		PersistentData = 1,
		Checkpoint = 2,
	};

	enum class SaveSyncAckStatus : std::uint8_t
	{
		ChunkReceived = 1,
		TransferVerified = 2,
		TransferFailed = 3,
	};

	enum class ProjectileEventKind : std::uint8_t
	{
		PepperSpawn = 1,
		ClockBombSpawn = 2,
		ClockBombUpdate = 3,
		ClockBombExplode = 4,
		ClockBombRemove = 5,
		// Teapot Cannon shell. Same 68-byte payload: rotation[] carries the
		// trace's DestLocation as float bits, extra its FlightTime, reserved
		// the flight template hash, projectileId's high half the muzzle hash,
		// variant = level | 0x80 when charged.
		TeapotSpawn = 6,
		// One-shot jump/float/glide emitter: reserved = template hash,
		// location = offset from the pawn, rotation = emitter rotation.
		BodyEffect = 7,
		// Float (hold jump) emitter state: variant bit0 = on, reserved =
		// template hash. Repeated every 250ms while on, 3x when it ends.
		FloatState = 8,
		// The shooter's pepper bullet / teapot shell ended (Destroyed):
		// projectileId = the id its *Spawn event carried, variant 0 pepper /
		// 1 teapot, location = where it ended. The receiver explodes its
		// cosmetic copy right there, at that moment.
		ProjectileImpact = 9,
	};

	enum class SharedWorldEventKind : std::uint8_t
	{
		EnemyDamageRequest = 1,
		EnemyAuthoritativeState = 2,
		VentStateApplied = 3,
		InteractionUsed = 4,
		InteractionMatineeStarted = 5,
		InteractionInLondon = 6,
		InteractionTriggerUsed = 7,
		InteractionContextActionActivated = 8,
		InteractionContextActorStarted = 9,
		BreakableDestroyed = 10,
		PlayerDamageRequest = 11,
		// Carries a hashed AnimNotify_PlayParticleEffect name in entityKey.
		ParticleNotify = 12,
	};

	enum SharedWorldEventFlags : std::uint8_t
	{
		SharedWorldEnemyDead = 1u << 0,
	};

	enum SharedEnemyPoseFlags : std::uint32_t
	{
		SharedEnemyPoseHidden = 1u << 0,
		SharedEnemyPoseFighting = 1u << 1,
		// The host still owns health/death and encounter progression, but the
		// client's native AI owns movement while pursuing the real client
		// Alice. The client returns that pawn pose in ClientCommandPayload.
		SharedEnemyPoseClientAuthority = 1u << 2,
		// Bit 3: the shield bits below are valid (the enemy has shields).
		// Bits 4..11: ShieldComponentsArray[i].bInShield for i < 8. Armour
		// is toggled by animation notifies (AliceAnimNotify_ToggleShield),
		// which do not run on a copy that only follows poses - the client's
		// Menacing Ruin stayed armoured for good and only the host could
		// ever hurt it.
		SharedEnemyPoseShieldValid = 1u << 3,
		SharedEnemyPoseShieldShift = 4,
		SharedEnemyPoseShieldMask = 0xFFu << 4,
		// Upper 16 bits carry a compact class signature. This lets a client
		// recover a binding when a dynamically spawned enemy has a different
		// initial position (and therefore a different stable entity key).
		SharedEnemyPoseClassShift = 16,
		SharedEnemyPoseClassMask = 0xFFFF0000u,
	};

	enum class Role : std::uint8_t
	{
		Unknown = 0,
		Host = 1,
		Client = 2,
	};

	enum StateFlags : std::uint32_t
	{
		StateVisible = 1u << 0,
		StateWalking = 1u << 1,
		StateCrouched = 1u << 2,
		StateInCombat = 1u << 3,
		StateShrunk = 1u << 4,
		StateCinematic = 1u << 5,
		StateActionActive = 1u << 6,
		StateAuthoritative = 1u << 7,
		StateBodyHidden = 1u << 8,
		StateUpperBodyHidden = 1u << 9,
		StateHairHidden = 1u << 10,
		StateSkirtHidden = 1u << 11,
		StateBowHidden = 1u << 12,
		StateRibbonHidden = 1u << 13,
		StateEarHidden = 1u << 14,
		StateWeaponHidden = 1u << 15,
		StateForceCutscene = 1u << 16,
		StateProgressionValid = 1u << 17,
		// The sender's Alice is in hysteria (bInHysteriaMode).
		StateHysteria = 1u << 18,
		// The sender's weapon is faded out (AlicePawn.FadeOutWeapon: dodge,
		// idle put-away, weapon switch) - WeaponForAlice.bFadeToHide or its
		// CurMeshComponent force-translucency heading to alpha 0.
		StateWeaponFaded = 1u << 19,
	};

	enum HostCommandFlags : std::uint32_t
	{
		HostCommandSummonClient = 1u << 0,
		HostCommandRestartCheckpoint = 1u << 1,
		HostCommandReturnToMenu = 1u << 2,
	};

	enum ClientCommandFlags : std::uint32_t
	{
		ClientCommandRequestRestart = 1u << 0,
		ClientCommandRequestReturnToMenu = 1u << 1,
	};

	enum class PlayerAction : std::uint8_t
	{
		None = 0,
		MeleeAttack = 1,
		WeaponAttack = 2,
		RightClickAttack = 3,
		StartFire = 4,
		StopFire = 5,
		Dodge = 6,
		Jump = 7,
		ShrinkEnter = 8,
		ShrinkLeave = 9,
		WeaponSwitch = 10,
		// Fire button pressed/released with a chargeable weapon (the Teapot).
		// StartFire only arrives with the actual shot, too late for the steam
		// that rises while the charge builds.
		ChargeStart = 11,
		ChargeStop = 12,
		// Alice reappeared at a checkpoint (AlicePlayerController.RespawnAlice
		// or the SM_Respawn special move): play the respawn effect.
		Respawn = 13,
	};

	enum class AnimationComponent : std::uint8_t
	{
		Body = 0,
		UpperBody = 1,
		Weapon = 2,
	};

	enum AnimationSequenceFlags : std::uint8_t
	{
		AnimationSequenceLooping = 1u << 0,
		AnimationSequenceRelevant = 1u << 1,
		AnimationSequenceCustom = 1u << 2,
		AnimationSequenceAction = 1u << 3,
	};

	enum AnimationBlendFlags : std::uint8_t
	{
		AnimationBlendRelevant = 1u << 0,
		AnimationBlendCustom = 1u << 1,
	};

#pragma pack(push, 1)
	struct Header
	{
		std::uint32_t magic = Magic;
		std::uint16_t version = Version;
		PacketType type = PacketType::Hello;
		std::uint32_t payloadSize = 0;
		std::uint32_t sessionId = 0;
		std::uint32_t playerId = 0;
		std::uint32_t sequence = 0;
	};

	struct HelloPayload
	{
		Role role = Role::Unknown;
		std::uint8_t reserved[3]{};
		std::uint32_t processId = 0;
		char label[32]{};
	};

	struct WelcomePayload
	{
		std::uint32_t assignedPlayerId = 0;
		std::uint32_t heartbeatMs = 1000;
		std::uint8_t accepted = 0;
		std::uint8_t reserved[3]{};
		char message[64]{};
	};

	struct AnimationSequencePayload
	{
		char sequenceName[48]{};
		float position = 0.0f;
		float rate = 1.0f;
		std::uint16_t nodeIndex = 0;
		AnimationComponent component = AnimationComponent::Body;
		std::uint8_t flags = 0;
		float nodeWeight = 0.0f;
	};

	struct AnimationBlendPayload
	{
		std::uint16_t nodeIndex = 0;
		std::int16_t activeChildIndex = 0;
		AnimationComponent component = AnimationComponent::Body;
		std::uint8_t flags = 0;
		float nodeWeight = 0.0f;
	};

	struct AnimationGraphPayload
	{
		std::uint32_t frameNumber = 0;
		std::uint32_t mapHash = 0;
		std::uint32_t actorId = 0;
		std::uint64_t clientTimeMs = 0;
		std::uint8_t sequenceCount = 0;
		std::uint8_t blendCount = 0;
		// Was two reserved bytes; now a 16-bit hash of an
		// AnimNotify_PlayParticleEffect to replay on the proxy, or zero for
		// none. It has to live inside the existing two bytes because the relay
		// validates each packet's payload size against its own copy of this
		// header: growing this struct by even four bytes stopped type 9 being
		// forwarded at all, which took the proxy's animation with it. Sixteen
		// bits over a few hundred notify objects collides about once across
		// the whole game, and the cost of a collision is one wrong spark.
		std::uint16_t particleNotifyHash = 0;
		AnimationSequencePayload sequences[MaxAnimationSequences]{};
		AnimationBlendPayload blends[MaxAnimationBlends]{};
	};

	struct ProjectileEventPayload
	{
		std::uint32_t eventSerial = 0;
		std::uint32_t mapHash = 0;
		std::uint32_t actorId = 0;
		std::uint32_t projectileId = 0;
		std::uint64_t clientTimeMs = 0;
		ProjectileEventKind kind = ProjectileEventKind::PepperSpawn;
		std::uint8_t variant = 0;
		std::uint16_t reserved = 0;
		float location[3]{};
		std::int32_t rotation[3]{};
		float velocity[3]{};
		float extra = 0.0f;
	};

	struct SharedWorldEventPayload
	{
		std::uint32_t eventSerial = 0;
		std::uint32_t mapHash = 0;
		std::uint32_t actorId = 0;
		std::uint32_t originActorId = 0;
		std::uint64_t entityKey = 0;
		std::uint64_t clientTimeMs = 0;
		SharedWorldEventKind kind =
			SharedWorldEventKind::EnemyDamageRequest;
		std::uint8_t flags = 0;
		std::uint16_t reserved = 0;
		std::int32_t damage = 0;
		std::int32_t health = 0;
		std::int32_t healthMax = 0;
		float hitLocation[3]{};
		float momentum[3]{};
		char damageType[64]{};
	};

	struct PlayerStatePayload
	{
		char mapName[64]{};
		std::uint32_t actorId = 0;
		float location[3]{};
		std::int32_t rotation[3]{};
		float velocity[3]{};
		float drawScale = 1.0f;
		float drawScale3D[3]{ 1.0f, 1.0f, 1.0f };
		float meshTranslation[3]{};
		float meshScale = 1.0f;
		float meshScale3D[3]{ 1.0f, 1.0f, 1.0f };
		float collisionRadius = 0.0f;
		float collisionHeight = 0.0f;
		std::int32_t health = 0;
		std::int32_t healthMax = 0;
		std::uint32_t flags = StateVisible;
		std::uint32_t actionSerial = 0;
		std::uint64_t clientTimeMs = 0;
		std::uint64_t cutsceneBarrierKey = 0;
		std::uint8_t physics = 0;
		std::uint8_t movementState = 0;
		std::uint8_t specialMove = 0;
		std::uint8_t jumpStatus = 0;
		PlayerAction action = PlayerAction::None;
		std::uint8_t weaponType = 0;
		std::uint8_t archetype = 0;
		std::uint8_t dodgeStatus = 0;
		std::uint8_t weaponLevels[4]{};
		// One bit per EAliceAbilityControl value (0..17). Weapon inventory
		// actors and upgrade levels alone are not enough for a clean profile:
		// Aiming and the range-weapon UI are gated by these persistent flags.
		std::uint32_t abilityMask = 0;
	};

	struct SharedEnemyPosePayload
	{
		std::uint64_t entityKey = 0;
		float location[3]{};
		std::int32_t rotation[3]{};
		float velocity[3]{};
		std::int32_t health = 0;
		std::uint32_t flags = 0;
		std::uint8_t physics = 0;
		std::uint8_t npcState = 0;
		std::uint8_t healthState = 0;
		std::uint8_t aiState = 0;
	};

	struct ClientCommandPayload
	{
		PlayerStatePayload desiredState{};
		float input[4]{};
		std::uint32_t buttons = 0;
		std::uint32_t commandNumber = 0;
		std::uint8_t enemyCount = 0;
		std::uint8_t reserved[3]{};
		SharedEnemyPosePayload enemies[MaxSharedEnemies]{};
	};

	struct HostSnapshotPayload
	{
		PlayerStatePayload hostState{};
		PlayerStatePayload clientState{};
		std::uint32_t snapshotNumber = 0;
		std::uint32_t worldEpoch = 0;
		std::uint64_t hostTimeMs = 0;
		std::uint32_t commandSerial = 0;
		std::uint32_t commandFlags = 0;
		std::uint8_t enemyCount = 0;
		std::uint8_t reserved[3]{};
		SharedEnemyPosePayload enemies[MaxSharedEnemies]{};
	};

	struct PeerLeftPayload
	{
		std::uint32_t playerId = 0;
		Role role = Role::Unknown;
		std::uint8_t reserved[3]{};
	};

	// Save synchronization is deliberately a separate reliable layer over the
	// UDP relay. The client never writes a partial transfer: both files are
	// staged, SHA-256 checked, and committed together only after every chunk is
	// present.
	struct SaveSyncRequestPayload
	{
		std::uint32_t transferId = 0;
		std::uint32_t flags = 0;
	};

	struct SaveSyncFileManifest
	{
		SaveSyncFileKind kind = SaveSyncFileKind::PersistentData;
		std::uint8_t reserved0 = 0;
		std::uint16_t chunkCount = 0;
		std::uint32_t byteCount = 0;
		std::uint8_t sha256[32]{};
	};

	struct SaveSyncManifestPayload
	{
		std::uint32_t transferId = 0;
		SaveSyncFileManifest files[SaveSyncFileCount]{};
		float completionPercent = 0.0f;
		float playedHours = 0.0f;
		float playedMinutes = 0.0f;
	};

	struct SaveSyncChunkPayload
	{
		std::uint32_t transferId = 0;
		SaveSyncFileKind kind = SaveSyncFileKind::PersistentData;
		std::uint8_t reserved0 = 0;
		std::uint16_t chunkIndex = 0;
		std::uint16_t chunkCount = 0;
		std::uint16_t dataSize = 0;
		std::uint32_t dataChecksum = 0;
		std::uint8_t data[SaveSyncChunkBytes]{};
	};

	struct SaveSyncAckPayload
	{
		std::uint32_t transferId = 0;
		SaveSyncFileKind kind = SaveSyncFileKind::PersistentData;
		SaveSyncAckStatus status = SaveSyncAckStatus::ChunkReceived;
		std::uint16_t chunkIndex = 0;
		std::uint32_t detail = 0;
	};
#pragma pack(pop)

	template <typename T>
	struct Packet
	{
		Header header;
		T payload;
	};

	inline bool IsValidHeader(const Header& header, std::size_t datagramSize)
	{
		return header.magic == Magic
			&& header.version == Version
			&& header.payloadSize <= MaxDatagramSize - sizeof(Header)
			&& datagramSize == sizeof(Header) + header.payloadSize;
	}

	template <typename T>
	inline Packet<T> MakePacket(PacketType type, std::uint32_t sessionId,
		std::uint32_t playerId, std::uint32_t sequence, const T& payload)
	{
		static_assert(std::is_trivially_copyable_v<T>);
		Packet<T> packet{};
		packet.header.type = type;
		packet.header.payloadSize = static_cast<std::uint32_t>(sizeof(T));
		packet.header.sessionId = sessionId;
		packet.header.playerId = playerId;
		packet.header.sequence = sequence;
		packet.payload = payload;
		return packet;
	}

	static_assert(sizeof(Header) == 24);
	static_assert(sizeof(HelloPayload) == 40);
	static_assert(sizeof(WelcomePayload) == 76);
	static_assert(sizeof(AnimationSequencePayload) == 64);
	static_assert(sizeof(AnimationBlendPayload) == 10);
	static_assert(sizeof(AnimationGraphPayload) == 992);
	static_assert(sizeof(ProjectileEventPayload) == 68);
	static_assert(sizeof(SharedWorldEventPayload) == 136);
	static_assert(sizeof(PlayerStatePayload) == 204);
	static_assert(sizeof(ClientCommandPayload) == 792);
	static_assert(sizeof(SharedEnemyPosePayload) == 56);
	static_assert(sizeof(HostSnapshotPayload) == 996);
	static_assert(sizeof(Header) + sizeof(HostSnapshotPayload)
		<= MaxDatagramSize);
	static_assert(sizeof(PeerLeftPayload) == 8);
	static_assert(sizeof(SaveSyncRequestPayload) == 8);
	static_assert(sizeof(SaveSyncFileManifest) == 40);
	static_assert(sizeof(SaveSyncManifestPayload) == 96);
	static_assert(sizeof(SaveSyncChunkPayload) == 916);
	static_assert(sizeof(SaveSyncAckPayload) == 12);
	static_assert(sizeof(Header) + sizeof(SaveSyncChunkPayload)
		<= MaxDatagramSize);
}
